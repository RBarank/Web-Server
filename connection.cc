#include "connection.hpp"
#include <boost/tokenizer.hpp>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "mime-types.hpp"
#include <iostream>
#include <unordered_map>
#include <cstring>
#include "server_info.hpp"
#include <boost/bind.hpp>


Connection::Connection(boost::asio::ip::tcp::socket socket, const std::unordered_map<std::string, 
		       RequestHandler*>& path_map, const std::unordered_map<std::string, std::string>& name_map)
  : socket_(std::move(socket)), path_map_(path_map), name_map_(name_map)
{
  
}

void Connection::Start()
{
  try 
    {
      DoRead();
    }
  catch(boost::system::error_code &e) 
    {
      throw e;
    }
}

void Connection::Stop()
{
  socket_.close();
}

void Connection::DoRead()
{
  auto self(shared_from_this());

  // Clear content buffer before every read
  memset(request_buffer_, 0, MAX_REQUEST_SIZE);
 
  boost::asio::async_read_until(socket_, buffer_, "\r\n\r\n",
				boost::bind(&Connection::HandleRead, shared_from_this()));
}

void Connection::HandleRead()
{
  //size_t request_buffer_size = bytes;
  std::ostringstream ss;
  ss << &buffer_;
  std::string buffer_string = ss.str();
  std::cout << "Buffer String : " << buffer_string << "\n";
  if(buffer_string == "")
    {
      return;
    }
  std::string first = "";
  int i = 0;
  while (buffer_string[i] != ' ')
    {
      first += buffer_string[i];
      i++;
    }
  if (!(first == "GET" || first == "POST" || first == "PUT" || first == "DELETE"))
    {
      std::cout << "Incomplete Request received!\n";
      return;
    }
  
  std::unique_ptr<Request> request(Request::Parse(buffer_string));  
  std::string request_uri;
  request_uri = request->GetUri();
  
  Response* response = new Response;
  RequestHandler* handler = GetRequestHandler(request_uri);
  
  if (handler != nullptr)
    {
      RequestHandler::Status ret = handler->HandleRequest(*request, response);
      
      if(ret == RequestHandler::Status::FILE_NOT_FOUND)
	{
	  request_uri = "/404";
	  path_map_[request_uri]->HandleRequest(*request, response);
	}
      RequestInfo request_info;
      request_info.url = request->GetUri();
      request_info.rc = response->ret_response_code();
      HandlerInfo handler_info;
      handler_info.type_of_handler = name_map_[request_uri];
      handler_info.url_prefix = request_uri;

      ServerInfo::getInstance().lock();
      ServerInfo::getInstance().append_request(request_info);
      ServerInfo::getInstance().append_handler(handler_info);
      ServerInfo::getInstance().unlock();
    }

  // if request accepts gzip encoding, pass response to the gzip-compression function
  if (request->AcceptsGzip())
    {
      response->ApplyGzip();
    }

  std::string response_string = response->ToString();
  boost::asio::write(socket_, boost::asio::buffer(response_string, response_string.size()));
}
    
void Connection::DoWrite()
{
  auto self(shared_from_this());
  
  boost::asio::async_write(socket_, boost::asio::buffer(request_buffer_),
			   [this, self](boost::system::error_code ec, std::size_t)
			   {
			     if (!ec)
			       {
				 boost::system::error_code ignored_ec;
				 Stop();
			       }
			   });
}

RequestHandler* Connection::GetRequestHandler(const std::string& path)
{
  std::string temp_path = path;
  while(temp_path.length() > 0) 
    {
      for(auto& handler_pair: path_map_) 
	{	
	  if (temp_path == handler_pair.first) 
	    {
	      return handler_pair.second;
            }
     	}
      std::size_t slash_found = temp_path.find_last_of("/");
      if (slash_found == 0 && temp_path == "/")
	{
	  break;
      	}
      temp_path = temp_path.substr(0, slash_found);
      if (slash_found == 0)
	{
	  temp_path = "/";
	}
    }
  return nullptr;
}

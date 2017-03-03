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

namespace http {
namespace server {

connection::connection(boost::asio::ip::tcp::socket socket, const std::unordered_map<std::string, RequestHandler*>& pathMap, const std::unordered_map<std::string, std::string>& nameMap)
  : socket_(std::move(socket)), pathMap_(pathMap), nameMap_(nameMap)
{

}

void connection::start()
{
  try 
    {
      do_read();
    }
  catch(boost::system::error_code &e) 
    {
      throw e;
    }
}

void connection::stop()
{
  socket_.close();
}

void connection::do_read()
{
  auto self(shared_from_this());

  // printf("IN CONNECTION::DO_READ\n");
  // Clear content buffer before every read
  memset(request_buffer, 0, MAX_REQUEST_SIZE);
  // printf("WE GOT HEREgoog\n");
  
    
    boost::asio::async_read_until(socket_, buffer_, "\r\n\r\n",
                                  boost::bind(&connection::handle_read, shared_from_this()));
  
}

void connection::handle_read()
    {
        //size_t request_buffer_size = bytes;
        std::ostringstream ss;
        ss << &buffer_;
        std::string bufferString = ss.str();
        std::cout << "Buffer string : " << bufferString << "\n";
        std::unique_ptr<Request> currentRequest(Request::Parse(bufferString));
        printf("IN CONNECTION::DO_READ ASYNC_READ_SOME\n");
        std::string request_base;
        
        Response* resp = new Response;
        RequestHandler* handler = GetRequestHandler(currentRequest->uri());
        
        std::cout << currentRequest->uri() << std::endl;
        //std::cout << request_base << std::endl;
        if (handler != nullptr){
            RequestHandler::Status ret = handler->HandleRequest(*currentRequest, resp);
            
            if(ret == RequestHandler::Status::FILE_NOT_FOUND){
                request_base = "/404";
                pathMap_[request_base]->HandleRequest(*currentRequest, resp);
            }
            RequestInfo req_info_;
            req_info_.url = currentRequest->uri();
            req_info_.rc = resp->ret_response_code();
            HandlerInfo handler_info_;
            handler_info_.type_of_handler = nameMap_[request_base];
            handler_info_.url_prefix = request_base;
            
            ServerInfo::getInstance().lock();
            ServerInfo::getInstance().append_request(req_info_);
            ServerInfo::getInstance().append_handler(handler_info_);
            ServerInfo::getInstance().unlock();
        }
        
        //          printf("WE GOT HEREamazballs\n");
        std::string respString = resp->ToString();
        boost::asio::write(socket_, boost::asio::buffer(respString, respString.size()));
    }
    
void connection::do_write()
{
  auto self(shared_from_this());
  
                                    // TODO: replace below with the actual response
  boost::asio::async_write(socket_, boost::asio::buffer(request_buffer),
      [this, self](boost::system::error_code ec, std::size_t)
      {
        if (!ec)
        {
          boost::system::error_code ignored_ec;
          stop();
        }
	});
}

RequestHandler* connection::GetRequestHandler(const std::string& path)
{
    std::string temp_path = path;
    while(temp_path.length() > 0) {
      	for(auto& handlerPair: pathMap_) {	
            //std::cout<< temp_path<<std::endl;
            //std::cout<< handlerPair.first<<std::endl;
	    if (temp_path == handlerPair.first) {
		        
                return handlerPair.second;
            }
     	}
     	std::size_t slash_found = temp_path.find_last_of("/");
     	if (slash_found == 0 && temp_path == "/")
            break;
      	temp_path = temp_path.substr(0, slash_found);
      	if (slash_found == 0)
            temp_path = "/";
    }
    return nullptr;
}

} // namespace server
} // namespace http

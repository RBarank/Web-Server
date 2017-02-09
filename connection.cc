#include "connection.hpp"
#include <boost/tokenizer.hpp>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "mime-types.hpp"
#include <iostream>

namespace http {
namespace server {

connection::connection(boost::asio::ip::tcp::socket socket)
  : socket_(std::move(socket))
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

  // Clear content buffer before every read
  memset(request_.content, 0, MAX_REQUEST_SIZE);
  
  socket_.async_read_some(boost::asio::buffer(request_.content),
      [this, self](boost::system::error_code ec, std::size_t bytes)
      {
	request_.length = bytes;
	// TODO: Handle num bytes read
       
	// TODO: For now always go to handle_request
	handle_request();

	do_write();

  });
}

// Handle Request to be an intermediary between do_read and do_write
void connection::handle_request()
{
  std::cout << "request begin\n" << request_.content << "response end" << std::endl;

  // use boost tokenizer to parse request
  const std::string req_str(request_.content);
  boost::char_separator<char> separator{" "};
  boost::tokenizer<boost::char_separator<char>> tokens(req_str, separator);
  boost::tokenizer<boost::char_separator<char>>::iterator tokens_it = tokens.begin();

  request_.method = *(tokens_it);
  ++tokens_it;
  request_.uri = *(tokens_it);
  
  std::cout << "request_method: " << request_.method << "\nrequest_uri: " << request_.uri << std::endl;

  if (request_.uri.substr(0, 6) == "/echo/")
    {
      request_.base = "echo";
      do_echo();
    }
  else if (request_.uri.substr(0, 8) == "/static/")
    {
      request_.base = "static";
      do_static();
    }
  else
    {
      // TODO: neither static nor echo base specified
      reply_ = reply::stock_reply(reply::bad_request);
      return;
    }
  
}

bool url_decode(const std::string& in, std::string& out)
{
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
} 

void connection::do_static()
{
  // TODO: error checking and input validation

  std::cout << "in do_static" << std::endl;

  // filepath beings after /static/ so at the 8th char
  std::string filepath = request_.uri.substr(7);
  std::cout << "filepath: " << filepath << std::endl;

  std::string request_path;
  if (!url_decode(filepath, request_path))
  {
    reply_ = reply::stock_reply(reply::bad_request);
    return;
  }

  //std::cout << "request path: " << request_path << std::endl;

  // Request path must be absolute and not contain "..".
  if (request_path.empty() || request_path[0] != '/'
      || (request_path.find("..") != std::string::npos))
  {
    reply_ = reply::stock_reply(reply::bad_request);
    return;
  }

  // If path ends in slash (i.e. is a directory) then add "index.html".
  // TODO: why not return a bad request here??
  if (request_path[request_path.size() - 1] == '/')
  {
    request_path += "index.html";
  }

  std::size_t last_slash_pos = request_path.find_last_of("/");
  std::size_t last_dot_pos = request_path.find_last_of(".");
  std::string extension;
  if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
  {
    extension = request_path.substr(last_dot_pos + 1);
  }
  else
    {
      reply_ = reply::stock_reply(reply::bad_request);
      return;
    }

  // Open the file to send back.
  // TODO: why not treat file path from beginning as starting after the second "/" in /static/..
  std::string full_path = request_path.substr(1);

  //std::cout << "full path: " << full_path << std::endl;
  std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
  if (!is)
  {
    reply_ = reply::stock_reply(reply::not_found);
    return;
  }

  // Fill out the reply to be sent to the client.
  reply_.status = reply::ok;
  char buf[512];
  while (is.read(buf, sizeof(buf)).gcount() > 0)
    {
      reply_.content.append(buf, is.gcount());
      memset(buf, 0, sizeof(buf));
    }
  //std::cout << "content: " << reply_.content << std::endl; // Debugging
  reply_.headers.resize(2);
  reply_.headers[0].name = "Content-Length";
  reply_.headers[0].value = std::to_string(reply_.content.size());
  reply_.headers[1].name = "Content-Type";
  reply_.headers[1].value = mime_types::extension_to_type(extension);  
  //std::cout << "type: " << reply_.headers[1].value << std::endl; // Debugging


  //stop();
}

void connection::do_echo()
{
  std::cout << "in do_echo" << std::endl;

  auto self(shared_from_this());
  
  reply_.content.append(request_.content, request_.length);

  reply_.status = reply::ok;
  reply_.headers.resize(2);
  reply_.headers[0].name = "Content-Length";
  reply_.headers[0].value = std::to_string(reply_.content.size());
  reply_.headers[1].name = "Content-Type";
  reply_.headers[1].value = "text/plain";
}

void connection::do_write()
{
  auto self(shared_from_this());

  boost::asio::async_write(socket_, reply_.to_buffers(),
      [this, self](boost::system::error_code ec, std::size_t)
      {
        if (!ec)
        {
          boost::system::error_code ignored_ec;
          stop();
        }
	});
}



} // namespace server
} // namespace http

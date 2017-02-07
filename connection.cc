#include "connection.hpp"
#include <boost/tokenizer.hpp>
#include <utility>
#include <vector>

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

	/*
        reply_.content.append(request_.content, bytes);
	if (reply_.content.substr(reply_.content.size() - 4, 4) == "\r\n\r\n" )
	  {
	    // call parse_request instead
	    // parse_request(...)
	    //do_write();
	    handle_request();
	  }
        else
	  {
	    do_read();
	  }*/
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
  

  /*
  std::string segment;
  size_t i =  0;
  bool method_parsed = false;

  while (i < request_.length)
    {
      segment += request_.content[i];
      if (request_.content[i] == ' ')
	{
	  if (method_parsed == false)
	    {
	      request_.method = segment;
	      method_parsed = true;
	      std::cout << "method " << request_.method << std::endl;
	    }
	  else
	    {
	      request_.uri = segment;
	      std::cout << "uri " << request_.uri << std::endl;
	      break;
	    }
	  segment = "";
	}
      i++;
    }
  */

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
    }
  
/*
  std::cout << "request base: " << request_.base << std::endl;
  std::cout << request_.method << "   " << request_.uri << std::endl;
  do_echo();*/  
}
 

void connection::do_static()
{
  // TODO: error checking and input validation

  std::cout << "in do_static" << std::endl;

  // for now, handle only .html
  // TODO: add definition of supported file extensions in request.hpp

  // filepath beings after /static/ so at the 8th char
  std::string filepath = request_.uri.substr(8, std::string::npos);
  std::cout << "filepath: " << filepath << std::endl;

  size_t pos = filepath.find_last_of(".");
  std::string file_type;
  if (pos != std::string::npos)
    {
      file_type = filepath.substr(pos+1);
    }
  std::cout << "file type: " << file_type << std::endl;  

  stop();
}


// This is the same as the old do_write
void connection::do_echo()
{
  std::cout << "in do_echo" << std::endl;

  auto self(shared_from_this());
  
  reply_.content.append(request_.content, request_.length);

  reply_.status = reply::ok;
  header head0;
  head0.name = "Content-Length";
  head0.value = std::to_string(reply_.content.size());
  reply_.headers.push_back(head0);
        
  header head1;
  head1.name = "Content-Type";
  head1.value = "text/plain";
  reply_.headers.push_back(head1);

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
/*
    
void connection::do_write()
{
  auto self(shared_from_this());
  reply_.status = reply::ok;
  header head0;
  head0.name = "Content-Length";
  head0.value = std::to_string(reply_.content.size());
  reply_.headers.push_back(head0);
        
  header head1;
  head1.name = "Content-Type";
  head1.value = "text/plain";
  reply_.headers.push_back(head1);

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
*/


} // namespace server
} // namespace http

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

connection::connection(boost::asio::ip::tcp::socket socket, const std::unordered_map<std::string, std::string>& pathMap)
  : socket_(std::move(socket)), pathMap_(pathMap)
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
  memset(request_buffer, 0, MAX_REQUEST_SIZE);
  
  socket_.async_read_some(boost::asio::buffer(request_buffer),
			  [this, self](boost::system::error_code ec, std::size_t bytes)
			  {
			    //size_t request_buffer_size = bytes;
			    //std::string bufferString(request_buffer);

			    //TODO: call parse method of request
			    //parseRequest();
			    /*
			    if (pathMap_.find(request_.base) != pathMap_.end()){
			      request_handler* currentHandler = request_handler::generateHandler(request_.base, pathMap_.find(request_.base)->second);
			      if(currentHandler != NULL)
				currentHandler->handle_request(request_, reply_);
			      else
				reply_ = Response::stock_reply(Response::bad_request);
			      delete currentHandler;
			    }
			    else
			      reply_ = Response::stock_reply(Response::bad_request);
			    */
			    do_write();
			    
			  }); 
  
}

// Handle Request is called by do_read, uses request_ to properly fill out reply_, then calls do_write()
// void connection::parseRequest()
// {
//   std::cout << "request begin\n" << request_.content << "response end" << std::endl;

//   // use boost tokenizer to parse request
//   const std::string req_str(request_.content);
//   boost::char_separator<char> separator{" "};
//   boost::tokenizer<boost::char_separator<char>> tokens(req_str, separator);
//   boost::tokenizer<boost::char_separator<char>>::iterator tokens_it = tokens.begin();

//   request_.method = *(tokens_it);
//   ++tokens_it;
//   request_.uri = *(tokens_it);
  
//   std::cout << "request_method: " << request_.method << "\nrequest_uri: " << request_.uri << std::endl;

//   size_t secondSlash = request_.uri.substr(1).find_first_of("/");
//   request_.base = request_.uri.substr(0,secondSlash + 1);
//   std::cout << "request_base: " << request_.base << std::endl;
// }

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



} // namespace server
} // namespace http

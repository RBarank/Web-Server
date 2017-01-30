#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <utility>
#include "connection.hpp"
#include <vector>

namespace http {
namespace server {

connection::connection(boost::asio::ip::tcp::socket socket)
  : socket_(std::move(socket))
{
}

void connection::start()
{
  do_read();
}

void connection::stop()
{
  socket_.close();
}

void connection::do_read()
{
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(buffer_),
      [this, self](boost::system::error_code ec, std::size_t bytes)
      {
        reply_.append(buffer_.data(), buffer_.data() + bytes);
        if (reply_.substr(reply_.size() - 4, 4) == "\r\n\r\n" )
          do_write();
        else
          do_read();
      });
}

void connection::do_write()
{
  auto self(shared_from_this());
  
  std::vector<boost::asio::const_buffer> buffers;
  std::string sendString = "";
  sendString.append("HTTP/1.0 200 OK\r\n");

  sendString.append("Content-Length");
  sendString.append(": ");
  sendString.append(std::to_string(reply_.size()));
  sendString.append("\r\n");

  sendString.append("Content-Type");
  sendString.append(": ");
  sendString.append("text/plain\r\n\r\n");
  
  sendString.append(reply_);

  buffers.push_back(boost::asio::buffer(sendString));
  
    boost::asio::async_write(socket_, buffers,
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

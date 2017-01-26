#include "config_parser.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>

#include "server.hpp"
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
        reply_.content.append(buffer_.data(), buffer_.data() + bytes);
        if (reply_.content.substr(reply_.content.size() - 4, 4) == "\r\n\r\n" )
          do_write();
        else
          do_read();
      });
}

void connection::do_write()
{
  auto self(shared_from_this());
  
  reply_.status = reply::ok;
  header head0;
  head0.name = "Content-Length";
  head0.value = std::to_string(reply_.content.size());
  reply_.headers.push_back(head0);
  //reply_.headers[0].name = "Content-Length";
  //reply_.headers[0].value= std::to_string(reply_.content.size());
  header head1;
  head1.name = "Content-Type";
  head1.value = "text/plain";
  reply_.headers.push_back(head1);
  //reply_.headers[1].name = "Content-Type";
  //reply_.headers[1].value = "text/plain";
  
  /*
  std::vector<boost::asio::const_buffer> buffers;
  buffers.push_back(boost::asio::buffer("HTTP/1.0 200 OK\r\n"));

  buffers.push_back(boost::asio::buffer("Content-Length"));
  buffers.push_back(boost::asio::buffer(": "));
  buffers.push_back(boost::asio::buffer(std::to_string(reply_.content.size())));
  buffers.push_back(boost::asio::buffer("\r\n"));

  buffers.push_back(boost::asio::buffer("Content-Type"));
  buffers.push_back(boost::asio::buffer(": "));
  buffers.push_back(boost::asio::buffer("text/plain"));
  buffers.push_back(boost::asio::buffer("\r\n"));

  buffers.push_back(boost::asio::buffer("\r\n"));
  buffers.push_back(boost::asio::buffer(reply_.content));
  */
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

server::server(const std::string& address, const std::string& port)
  : io_service_(),
    acceptor_(io_service_),
    socket_(io_service_)
    {

  // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
  boost::asio::ip::tcp::resolver resolver(io_service_);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();

  do_accept();
}

void server::run()
{
  io_service_.run();
}

void server::do_accept()
{
  acceptor_.async_accept(socket_,
      [this](boost::system::error_code ec)
      {
        // Check whether the server was stopped by a signal before this
        // completion handler had a chance to run.
        if (!acceptor_.is_open())
        {
          return;
        }
        if (!ec)
        {
          std::make_shared<connection>(std::move(socket_))->start();
        }
        do_accept();
      });
}

} // namespace server
} // namespace http




int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./webserver <path to config file>\n");
        return 1;
    }
    
    NginxConfigParser config_parser;
    NginxConfig config;
    config_parser.Parse(argv[1], &config);
    
    std::string config_string = config.ToString().c_str();
    //std::cout << config_string << std::endl;
    
    GetPortNumber port_stuff = GetPortNumber(config);
    int port_number = port_stuff.portNumber();

    try
    {

        http::server::server s("127.0.0.1", std::to_string(port_number));

        s.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
    
    //std::cout << port_number;

    
    
    
    
    /*
     size_t port_location = config_string.find("listen \D.*");
     if (port_location == -1)
     {
     printf("Listen not found in config string\n");
     exit(1);
     }
     port_location += 7; // the portno starts 7 chars after the l in listen
     string port_string = "";
     while (isdigit(config_string[port_location]))
     {
     
     }
     
     
     
     printf("The portno is %d\n", portno);
     
     
     
     
     return 0;
     */
}

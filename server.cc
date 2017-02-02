#include "server.hpp"
#include "connection.hpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>



namespace http {
    namespace server {
        
        server::server(const std::string& address, const std::string& port)
        : io_service_(),
        acceptor_(io_service_),
        socket_(io_service_)
        {
            int port_number = std::stoi(port);
            if (port_number < 1 || port_number > 65535)
            {
                throw boost::system::errc::make_error_code(boost::system::errc::invalid_argument);
            }
            
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
            try {
                io_service_.run();
            } catch (boost::system::error_code const &e) {
                throw e;
            }
        }
        
        void server::do_accept()
        {
            try {
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
            } catch (boost::system::error_code const &e) {
                throw e;
            }
            
        }
        
    } // namespace server
} // namespace http




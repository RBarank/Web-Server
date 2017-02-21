#include "server.hpp"
#include "connection.hpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>

const int MAX_PORT_NO = 65535;
const int MIN_PORT_NO = 1;

namespace http {
  namespace server {
        
    server::server(const std::string& address, const NginxConfig& config)
      : io_service_(),
        acceptor_(io_service_),
        socket_(io_service_),
	portno_(-1)
    {
      if (!get_config_info(config))
	{
	  throw boost::system::errc::make_error_code(boost::system::errc::invalid_argument);
	}
      
      std::string port = std::to_string(portno_);
      std::cout << port << std::endl;

      for (auto const& x : uri_to_handler_map)
	{
	  std::cout << x.first << " " << x.second << std::endl;
	}

      // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
      boost::asio::ip::tcp::resolver resolver(io_service_);
      boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, std::to_string(portno_)});
      acceptor_.open(endpoint.protocol());
      acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
      acceptor_.bind(endpoint);
      acceptor_.listen();
      
      //do_accept(pathMap);
    }
    
    bool server::get_config_info(const NginxConfig& config)
    {
      std::map<std::string, bool> handlers_created;

      for (const auto& statement : config.statements_)
	{
	  if (statement->tokens_[0] == "port" && statement->tokens_.size() == 2)
	    {
	      std::string port_string = statement->tokens_[1];
	      if (port_string.length() > 5)
		{
		  return false;
		}
	      for (unsigned i = 0; i < port_string.length(); i++)
		{
		  if (!isdigit(port_string[i]))
		    {
		      return false;
		    }
		}

	      portno_ = std::stoi(port_string);

	      // port number not in valid range   
	      if(portno_ < MIN_PORT_NO || portno_ > MAX_PORT_NO)
		{
		  return false;
		}
	    }
	  else if (statement->tokens_[0] == "path" && statement->tokens_.size() == 3)
	    {

	      std::string uri_prefix = statement->tokens_[1];
	      std::string handler_name = statement->tokens_[2];
	      
	      const auto find_handler = uri_to_handler_map.find(uri_prefix);
	      if (handlers_created[handler_name])
		{
		  uri_to_handler_map[uri_prefix] = find_handler.second();
		}
	      
	      uri_to_handler_map[uri_prefix] = RequestHandler::CreateByName(handler_name);
	      uri_to_handler_map[uri_prefix].Init(uri_prefix, statement->child_block_);
	      handlers_created[handler_name] = true;

	      // auto handler = RequestHandler::CreateByName(handler_name, statement_->child_block);                                                                        
	      // handler_map[uri_prefix] = handler                                                                                                                          
	      // TODO: handle duplicate and invalid paths                                                                                                                   



	    }
	}
      // if the port number is uninitialized or the handler map is empty, our server should not start
      if (portno_ == -1 || uri_to_handler_map.empty())
	{
	  return false;
	}

      return true;
    }
        
    void server::run()
    {
      try {
	io_service_.run();
      } catch (boost::system::error_code const &e) {
	throw e;
      }
    }
    
    void server::do_accept(const std::unordered_map<std::string, std::string>& pathMap)
    {
      try {
	acceptor_.async_accept(socket_,
			       [this, &pathMap](boost::system::error_code ec)
			       {
				 // Check whether the server was stopped by a signal before this
				 // completion handler had a chance to run.
				 if (!acceptor_.is_open())
				   {
				     return;
				   }
				 if (!ec)
				   {
				     std::make_shared<connection>(std::move(socket_), pathMap)->start();
				   }
				 do_accept(pathMap);
			       });
      } catch (boost::system::error_code const &e) {
	throw e;
      }
      
    }
    
  } // namespace server
} // namespace http




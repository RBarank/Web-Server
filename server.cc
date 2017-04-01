#include "server.hpp"
#include "connection.hpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>


const int MAX_PORT_NO = 65535;
const int MIN_PORT_NO = 1;

        
Server::Server(const std::string& address, const NginxConfig& config)
  : io_service_(),
    acceptor_(io_service_),
    socket_(io_service_),
    port_number_(-1)
{
  
  printf("IN SERVER CONSTRUCTOR\n");
  
  if (!GetConfigInfo(config))
    {
      printf("Config file incorrect. Waiting for a correct config file!\n");
      //throw boost::system::errc::make_error_code(boost::system::errc::invalid_argument);
      return;
    }
  
  SetThreads(config);
  
  // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
  boost::asio::ip::tcp::resolver resolver(io_service_);
  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port_number_);
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();
  
  
  DoAccept();
}

bool Server::GetConfigInfo(const NginxConfig& config)
{
  
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
	  
	  port_number_ = std::stoi(port_string);
	  
	  // port number not in valid range   
	  if(port_number_ < MIN_PORT_NO || port_number_ > MAX_PORT_NO)
	    {
	      return false;
	    }
	}
      else if (statement->tokens_[0] == "path" && statement->tokens_.size() == 3)
	{
	  // TODO: check for multiple paths mapping to handler with the same name
	  
	  std::string uri_prefix = statement->tokens_[1];
	  std::string handler_name = statement->tokens_[2];
       
	  RequestHandler* handler = RequestHandler::CreateByName(handler_name);
	  
	  // create by name will return a nullptr if it can't find a handler with this name or there is some error
	  if (handler == nullptr)
	    {
	      printf("handler is a nullptr!\n");
	      return false;
	    }
	  
	  // TODO: check return status of init and handle errors
	  
	  handler->Init(uri_prefix, *(statement->child_block_)); // get rid of this and replace with below
	  /* Status handler_init_status = handler.Init(uri_prefix, statement->child_block_);
	     if (handler_init_status == TODO_BAD_STATUS)
	     {
	     return false;
	     }*/
	  
	  uri_to_handler_map_[uri_prefix] = handler;
	  uri_to_handler_name_[uri_prefix] = handler_name;
	}
    }

  // if the port number is uninitialized or the handler map is empty, the server should not start
  // we need to to do this check in case we don't come across any config blocks with "port" or "path" terms
  if (port_number_ == -1 || uri_to_handler_map_.empty())
    {
      return false;
    }
  
  return true;
}

void Server::SetThreads(const NginxConfig& config)
{
  for (const auto& statement : config.statements_)
    {
      if (statement->tokens_[0] == "threads" && statement->tokens_.size() == 2)
	{
	  num_threads_ = std::stoi(statement->tokens_[1]);
	  return;
	}
    }
  num_threads_ = 4; // default number of threads
}

void Server::Run()
{
  for(int i = 0; i < num_threads_; i++)
    {
      std::shared_ptr<std::thread> thread(new std::thread(boost::bind(&boost::asio::io_service::run, &io_service_)));
      threads_.push_back(thread);
    }
  for(int i = 0; i < num_threads_; i++)
    {
      threads_[i] -> join();
    }
}

void Server::DoAccept()
{
  try 
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
				   std::make_shared<Connection>(std::move(socket_), uri_to_handler_map_, uri_to_handler_name_)->Start();
				 }
			       DoAccept();
			     });
    } 
  catch (boost::system::error_code const &e) 
    {
      throw e;
    }
  
}

void Server::Kill()
{
  acceptor_.close();
  io_service_.stop();
  std::cout << "Destroyed the server\n"; 
}




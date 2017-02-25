#include "static_handler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace http{
  namespace server{
    
    RequestHandler::Status StaticHandler::Init(const std::string& uri_prefix, const NginxConfig& config)
    {
      uri_prefix_ = uri_prefix;
      for (const auto& statement : config.statements_){
	if (statement->tokens_[0] == "root" && statement->tokens_.size() == 2){
	  root_path_ = statement->tokens_[1];
	}
      }
      return RequestHandler::OK;
    }

    bool StaticHandler::url_decode(const std::string& in, std::string& out)
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
    

    RequestHandler::Status StaticHandler::HandleRequest(const Request& request, Response* response){
      // filepath beings after /static/ so at the 8th char
//        std :: cout << "URI : " << request.uri() << request.uri().length() << std::endl;
        if (request.uri().length() == 0)
        {
            *response = Response::stock_response(Response::bad_request);
            return RequestHandler::NOT_OK;
        }
      size_t secondSlash = request.uri().substr(1).find_first_of("/");
      std::string request_base = request.uri().substr(0,secondSlash + 1);
      std::string filepath = request.uri().substr(request_base.length());
        
      std::string request_path;
      if (!url_decode(filepath, request_path))
	{
//        std :: cout << "Did it here" << std::endl;
	  *response = Response::stock_response(Response::bad_request);
	  return RequestHandler::NOT_OK;
	}
      
      // Request path must be absolute and not contain "..".
      if (request_path.empty() || request_path[0] != '/'
	  || (request_path.find("..") != std::string::npos))
	  {
//          std :: cout << "Did it here2" << std::endl;
	    *response = Response::stock_response(Response::bad_request);
	    return RequestHandler::NOT_OK;
	  }
      
      // If path ends in slash (i.e. is a directory) then add "index.html".
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
    //std :: cout << "Did it here3" << std::endl;
	  *response = Response::stock_response(Response::bad_request);
	  return RequestHandler::NOT_OK;
	}
      
      // Open the file to send back.
      std::string full_path = root_path_ + request_path;
//        std::cout << root_path_ << "\n" ;
      full_path = full_path.substr(1);
      //std::cout << "filepath: " << pathMap_[request_.base] << std::endl;
      //std::cout << "full path: " << full_path << std::endl;
      std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
      if (!is)
	{
	  //*response = Response::stock_response(Response::not_found);
	  return RequestHandler::FILE_NOT_FOUND;
	}
      
      // Fill out the reply to be sent to the client.
      response->SetStatus(Response::ok);
      char buf[512];
      std::string content;
      while (is.read(buf, sizeof(buf)).gcount() > 0)
	{
	  content.append(buf, is.gcount());
	  memset(buf, 0, sizeof(buf));
	}
	  response->SetBody(content); 
      //std::cout << "content: " << response.content << std::endl; // Debugging
      // response.headers.resize(2);
      // response.headers[0].name = "Content-Length";
      // response.headers[0].value = std::to_string(response.content.size());
      // response.headers[1].name = "Content-Type";
      // response.headers[1].value = mime_types::extension_to_type(extension);
      response->AddHeader("Content-Length", std::to_string(content.size()));
      response->AddHeader("Content-Type", mime_types::extension_to_type(extension)); 
      //std::cout << "type: " << response.headers[1].value << std::endl; // Debugging
      return RequestHandler::OK;
    }
  } // namespace server
} // namespace http

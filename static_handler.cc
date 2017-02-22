#include "static_handler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace http{
  namespace server{

    Status Init(const std::string& uri_prefix, const NginxConfig& config)
    {
      return request_handler::OK;
    }
    


    /*
		static_handler::static_handler(std::string root)
			:fileRoot(root)
		{}

		bool static_handler::url_decode(const std::string& in, std::string& out)
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


		bool static_handler::handle_request(const request& request_, reply& reply_){
			// filepath beings after /static/ so at the 8th char
            
		  std::string filepath = request_.uri.substr(request_.base.length());

		  std::string request_path;
		  if (!url_decode(filepath, request_path))
		  {
		    reply_ = reply::stock_reply(reply::bad_request);
		    return false;
		  }

		  // Request path must be absolute and not contain "..".
		  if (request_path.empty() || request_path[0] != '/'
		      || (request_path.find("..") != std::string::npos))
		  {
		    reply_ = reply::stock_reply(reply::bad_request);
		    return false;
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
		      reply_ = reply::stock_reply(reply::bad_request);
		      return false;
		    }

		  // Open the file to send back.
		  std::string full_path = fileRoot + request_path;
		  full_path = full_path.substr(1);
		  //std::cout << "filepath: " << pathMap_[request_.base] << std::endl;
		  //std::cout << "full path: " << full_path << std::endl;
		  std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
		  if (!is)
		  {
		    reply_ = reply::stock_reply(reply::not_found);
		    return false;
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
		  return true;
		}
    */



  } // namespace server
} // namespace http

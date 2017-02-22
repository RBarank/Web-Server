#include "request_handler.hpp"
#include <map>

namespace http {
  namespace server {

    std::map<std::string, http::server::request_handler* (*)(void)>* request_handler_builders = nullptr;

    /*
    const std::string ECHO_URL = "/echo";
    const std::string STATIC_URL = "/static";
    request_handler* request_handler::generateHandler(std::string& url, std::string& root){
      if(url == ECHO_URL)
	return new echo_handler();
      else if(url == STATIC_URL && !root.empty())
	return new static_handler(root);
      else
	return NULL;
    }*/

    request_handler* request_handler::CreateByName(const std::string& type) 
    {
      const auto type_and_builder = request_handler_builders->find(type);
      if (type_and_builder == request_handler_builders->end()) 
    	{
    	  return nullptr;
    	}
      return (*type_and_builder->second)();
    }

  } // namespace server
} // namespace http

#inlcude "request_handler.hpp"

std::map<std::string, RequestHandler* (*)(void)>* request_handler_builders = nullptr;

namespace http {
  namespace server {
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

    RequestHandler* RequestHandler::CreateByName(const char* type) 
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

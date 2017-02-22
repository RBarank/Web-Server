#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <map>
#include <memory>

#include "request.hpp"
#include "reply.hpp"
#include "mime-types.hpp"
#include "config_parser.h"
#include "response.hpp"

namespace http {
  namespace server {

    // Represents the parent of all request handlers. Implementations should expect to
    // be long lived and created at server constrution.
    class request_handler {
     public:
      enum Status {
        OK = 0
        // Define your status codes here.
      };
      
      // Initializes the handler. Returns a response code indicating success or
      // failure condition.
      // uri_prefix is the value in the config file that this handler will run for.
      // config is the contents of the child block for this handler ONLY.
      virtual request_handler::Status Init(const std::string& uri_prefix,
                          const NginxConfig& config) = 0;

      // Handles an HTTP request, and generates a response. Returns a response code
      // indicating success or failure condition. If ResponseCode is not OK, the
      // contents of the response object are undefined, and the server will return
      // HTTP code 500.
      virtual request_handler::Status HandleRequest(const Request& request,
                                   Response* response) = 0;
    
      // Creates a request handler of the specified type
      static request_handler* CreateByName(const std::string& type);

    protected:
      std::string uri_prefix_; // TODO: make this a vector if we have handlers that handle multiple uri's
    };
    
    extern std::map<std::string, request_handler* (*)(void)>* request_handler_builders;
    template<typename T>
    class RequestHandlerRegisterer {
    public:
      RequestHandlerRegisterer(const std::string& type) {
	if (request_handler_builders == nullptr) {
	  request_handler_builders = new std::map<std::string, request_handler* (*)(void)>;
	}
	(*request_handler_builders)[type] = RequestHandlerRegisterer::Create;
      }
      static request_handler* Create() {
	return new T;
      }
    };
    
    #define REGISTER_REQUEST_HANDLER(ClassName)				\
      static RequestHandlerRegisterer<ClassName> ClassName##__registerer(#ClassName)
    

    
  } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP

#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "request.hpp"
#include "reply.hpp"
#include "mime-types.hpp"
#include "config_parser.h"

namespace http {
  namespace server {

    // class request_handler
    // {
    // public:
    // 	request_handler() {}
    //     virtual ~request_handler() {}
    // 	static request_handler* generateHandler(std::string& url, std::string& root);
    // 	virtual bool handle_request(const request& request_, reply& reply_)=0;
    // };

    // Represents the parent of all request handlers. Implementations should expect to
    // be long lived and created at server constrution.
    class request_handler {
     public:
      enum Status {
        OK = 0;
        // Define your status codes here.
      };
      
      // Initializes the handler. Returns a response code indicating success or
      // failure condition.
      // uri_prefix is the value in the config file that this handler will run for.
      // config is the contents of the child block for this handler ONLY.
      virtual Status Init(const std::string& uri_prefix,
                          const NginxConfig& config) = 0;

      // Handles an HTTP request, and generates a response. Returns a response code
      // indicating success or failure condition. If ResponseCode is not OK, the
      // contents of the response object are undefined, and the server will return
      // HTTP code 500.
      virtual Status HandleRequest(const Request& request,
                                   Response* response) = 0;
    };
    
  } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP

#ifndef ECHO_HANDLER_HPP
#define ECHO_HANDLER_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "request.hpp"
#include "response.hpp"
#include "request_handler.hpp"

namespace http {
  namespace server {

    class EchoHandler : public request_handler
    {
    public: 
      //echo_handler(){}
      //virtual ~echo_handler() {}
      
      //virtual bool handle_request(const request& request_, reply& reply_);
      // Initializes the handler. Returns a response code indicating success or
      // failure condition.
      // uri_prefix is the value in the config file that this handler will run for.
      // config is the contents of the child block for this handler ONLY.
      
      virtual Status Init(const std::string& uri_prefix,
                          const NginxConfig& config);

      // Handles an HTTP request, and generates a response. Returns a response code
      // indicating success or failure condition. If ResponseCode is not OK, the
      // contents of the response object are undefined, and the server will return
      // HTTP code 500.
      virtual Status HandleRequest(const Request& request,
                                   Response* response);
    };

    REGISTER_REQUEST_HANDLER(EchoHandler);
    
  } // namespace server
} // namespace http

#endif // ECHO_HANDLER_HPP

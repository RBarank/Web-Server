#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "request.hpp"
#include "response.hpp"

namespace http {
  namespace server {

    class request_handler
    {
      request_handler();
      virtual ~request_handler();
      virtual bool handle_request(const request& request_, response& response_);
    };
    
  } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP

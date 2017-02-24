#ifndef NOTFOUND_HANDLER_HPP
#define NOTFOUND_HANDLER_HPP

#include <string>
#include <vector>
#include "request.hpp"
#include "response.hpp"
#include "request_handler.hpp"

namespace http {
  namespace server {

    class NotFoundHandler : public request_handler
    {
    public:
      virtual Status Init(const std::string& uri_prefix,
                          const NginxConfig& config);
      virtual Status HandleRequest(const Request& request,
                                   Response* response);
    };

    REGISTER_REQUEST_HANDLER(NotFoundHandler);
  } // namespace server
} // namespace http

#endif // ECHO_HANDLER_HPP

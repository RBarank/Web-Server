#ifndef ECHO_HANDLER_HPP
#define ECHO_HANDLER_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "request.hpp"
#include "reply.hpp"
#include "request_handler.hpp"

namespace http {
  namespace server {

    class echo_handler : public request_handler
    {
    public: 
      echo_handler(){}
      virtual ~echo_handler() {}
      virtual bool handle_request(const request& request_, reply& reply_);
    };
    
  } // namespace server
} // namespace http

#endif // ECHO_HANDLER_HPP
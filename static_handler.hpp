#ifndef STATIC_HANDLER_HPP
#define STATIC_HANDLER_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "request.hpp"
#include "reply.hpp"
#include "request_handler.hpp"

namespace http {
  namespace server {

    class static_handler : public request_handler
    {
    	std::string fileRoot;
  	public:
  		static_handler(std::string root);
     	virtual ~static_handler() {}
     	bool url_decode(const std::string& in, std::string& out);
      	virtual bool handle_request(const request& request_, reply& reply_);
    };
    
  } // namespace server
} // namespace http

#endif // STATIC_HANDLER_HPP

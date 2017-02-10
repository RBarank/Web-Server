#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "request.hpp"
#include "reply.hpp"
#include "mime-types.hpp"

namespace http {
  namespace server {

    class request_handler
    {
    public:
    	request_handler() {}
        virtual ~request_handler() {}
    	static request_handler* generateHandler(std::string& url, std::string& root);
    	virtual bool handle_request(const request& request_, reply& reply_)=0;
    };
    
  } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP

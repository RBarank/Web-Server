#ifndef HTTP_REPLY_HPP
#define HTTP_REPLY_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "header.hpp"

namespace http {
	namespace server {

  		class Response {
  			std::vector<header> headers;
  			std::string content;
 		public:
  			enum ResponseCode {
    		// Define your HTTP response codes here.
  				ok = 200,
			  	created = 201,
			  	accepted = 202,
			  	no_content = 204,
			  	multiple_choices = 300,
			  	moved_permanently = 301,
			  	moved_temporarily = 302,
			  	not_modified = 304,
			  	bad_request = 400,
			  	unauthorized = 401,
			  	forbidden = 403,
			  	not_found = 404,
			  	internal_server_error = 500,
			  	not_implemented = 501,
			  	bad_gateway = 502,
			  	service_unavailable = 503
  			} status;
  
  			void SetStatus(const ResponseCode response_code);
  			void AddHeader(const std::string& header_name, const std::string& header_value);
  			void SetBody(const std::string& body);
  
  			std::string ToString();
  			std::vector<boost::asio::const_buffer> to_buffers();
      
		    /// Get a stock reply.
		    static Response stock_reply(status_type status);
		};

  }
}

#endif //HTTP_REPLY_HPP
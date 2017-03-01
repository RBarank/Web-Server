#include "gtest/gtest.h"
#include "proxy_handler.hpp"
#include <vector>
#include "config_parser.h"
#include "request_handler.hpp"
#include "response.hpp"
#include "request.hpp"

/**
      bool url_decode(const std::string& in, std::string& out);
      bool parse_remote_url(std::string remote_host_url);
      bool parse_remote_response(std::string remote_response);
      bool read_header(std::string headers);

      virtual Status Init(const std::string& uri_prefix, const NginxConfig& config);
      
      // Handles an HTTP request, and generates a response. Returns a response code
      // indicating success or failure condition. If ResponseCode is not OK, the
      // contents of the response object are undefined, and the server will return
      // HTTP code 500.
      virtual Status HandleRequest(const Request& request, Response* response);
**/

namespace http {
    namespace server{
        
        TEST(StaticHandler, INIT) {
			NginxConfigParser parser;
			NginxConfig out_config;
			ProxyHandler proxy_handler;
            std::stringstream config_stream("remote_host http://www.ucla.edu;");
			parser.Parse(&config_stream, &out_config);
			auto init_status = proxy_handler.Init("/", out_config);
			EXPECT_EQ(init_status, RequestHandler::Status::OK);
        }
   }//server
}//http

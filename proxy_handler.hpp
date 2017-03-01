#ifndef PROXY_HANDLER_HPP
#define PROXY_HANDLER_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "request.hpp"
#include "response.hpp"
#include "request_handler.hpp"

typedef std::vector<std::pair<std::string, std::string>> Headers;

namespace http {
  namespace server {

    class ProxyHandler : public RequestHandler
    {
      std::string uri_prefix_;
      std::string remote_host_whole_url;
      std::string protocol_;
      std::string host_url_;
      std::string path_;

      std::string response_headers, response_body, response_status, rest;
      Headers headers_;

      std::string remote_port_;
      bool url_decode(const std::string& in, std::string& out);
      bool parse_remote_url(std::string remote_host_url);
      bool parse_remote_response(std::string remote_response);
      bool read_header(std::string headers);
    public:
      //static_handler(std::string root);
      //      virtual ~static_handler() {}
    
      //virtual bool handle_request(const request& request_, reply& reply_);
      // Initializes the handler. Returns a response code indicating success or
      // failure condition.
      // uri_prefix is the value in the config file that this handler will run for.
      // config is the contents of the child block for this handler ONLY.
      virtual Status Init(const std::string& uri_prefix, const NginxConfig& config);
      
      // Handles an HTTP request, and generates a response. Returns a response code
      // indicating success or failure condition. If ResponseCode is not OK, the
      // contents of the response object are undefined, and the server will return
      // HTTP code 500.
      virtual Status HandleRequest(const Request& request, Response* response);
      
    };
    

    REGISTER_REQUEST_HANDLER(ProxyHandler);

  } // namespace server
} // namespace http

#endif // PROXY_HANDLER_HPP

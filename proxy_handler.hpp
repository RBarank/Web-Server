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

class ProxyHandler : public RequestHandler
{
public:
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
  
private:
  std::string uri_prefix_;
  std::string remote_host_whole_url_;
  std::string protocol_;
  std::string host_url_;
  std::string path_;
  std::string remote_port_;  
  std::string response_headers_;
  std::string response_body_;
  std::string response_status_;
  std::string rest_;
  Headers headers_;

  bool UrlDecode(const std::string& in, std::string& out);
  bool ParseRemoteUrl(std::string remote_host_url);
  bool ParseRemoteResponse(std::string remote_response);
  bool ReadHeader(std::string headers);
};
    

REGISTER_REQUEST_HANDLER(ProxyHandler);


#endif // PROXY_HANDLER_HPP

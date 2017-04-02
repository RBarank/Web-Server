#ifndef STATIC_HANDLER_HPP
#define STATIC_HANDLER_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "request.hpp"
#include "response.hpp"
#include "request_handler.hpp"


class StaticHandler : public RequestHandler
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
  std::string root_path_;

  // Extracts the url from "in" and returns it in "out".
  // Return false if it can't find a proper url.
  bool UrlDecode(const std::string& in, std::string& out) const;

  // Converts the string content, which represents is in  Markdown format,
  // to a string in html format and returns that string.
  std::string MarkdownToHtml(const std::string& content) const;
};

REGISTER_REQUEST_HANDLER(StaticHandler);


#endif // STATIC_HANDLER_HPP

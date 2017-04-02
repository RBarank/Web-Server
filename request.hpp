#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <memory>
#include <vector>
#include <boost/asio.hpp>

const int MAX_REQUEST_SIZE = 8192;


class Request 
{
public:
  
  static std::unique_ptr<Request> Parse(const std::string& raw_request);
  
  std::string GetRawRequest() const;
  std::string GetMethod() const;
  std::string GetUri() const;
  std::string GetVersion() const;
  std::string GetBody() const;
  
  using Headers = std::vector<std::pair<std::string, std::string>>;
  Headers GetHeaders() const;
  std::string GetHeaderByName(const std::string header_name) const;
  
  void SetRawRequest(std::string raw_request);
  void SetMethod(std::string method);
  void SetUri(std::string uri);
  void SetVersion(std::string version);
  void SetBody(std::string body);
  void SetHeaders(Headers headers);
  
  bool AcceptsGzip() const;
  
private:
  
  std::string raw_request_;
  std::string method_;
  std::string uri_;
  std::string version_;
  std::string body_;
  Headers headers_;
};
  
#endif // HTTP_REQUEST_HPP

#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>

    
class Response 
{
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
  };
  
  void SetStatus(const ResponseCode response_code);
  void AddHeader(const std::string& header_name, const std::string& header_value);
  bool SetHeader(const std::string header_name, const std::string header_value);
  void SetBody(const std::string& body);
  std::string ToString();
  static Response stock_response(ResponseCode status);
  ResponseCode ret_response_code() {return response_code_;}
  std::string body() const { return body_;};
  void ApplyGzip();
private:
  
  using Headers = std::vector<std::pair<std::string, std::string>>;
  Headers headers_;
  std::string body_;
  ResponseCode response_code_;
};


#endif //HTTP_RESPONSE_HPP

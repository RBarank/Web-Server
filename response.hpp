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
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NO_CONTENT = 204,
    MULTIPLE_CHOICES = 300,
    MOVED_PERMANENTLY = 301,
    MOVED_TEMPORARILY = 302,
    NOT_MODIFIED = 304,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503
  };
  
  void SetStatus(const ResponseCode response_code);
  void AddHeader(const std::string& header_name, const std::string& header_value);
  bool SetHeader(const std::string header_name, const std::string header_value);
  void SetBody(const std::string& body);
  std::string ToString() const;
  static Response CreateStockResponse(const ResponseCode status);
  ResponseCode ReturnResponseCode() const; 
  std::string GetBody() const;
  void ApplyGzip();
private:
  
  using Headers = std::vector<std::pair<std::string, std::string>>;
  Headers headers_;
  std::string body_;
  ResponseCode response_code_;
};


#endif //HTTP_RESPONSE_HPP

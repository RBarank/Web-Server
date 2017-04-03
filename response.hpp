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
  
  ResponseCode GetResponseCode() const; 
  std::string GetBody() const;

  void SetStatus(const ResponseCode response_code);
  bool SetHeader(const std::string header_name, const std::string header_value);
  void SetBody(const std::string& body);

  void AddHeader(const std::string& header_name, const std::string& header_value);

  // Converts the response to a single string and returns that string.
  // The string is created in this order: response code + headers + body
  std::string ToString() const;

  // Creates and returns a response whose data members are empty
  // except that its response code is equal to status
  static Response CreateStockResponse(const ResponseCode status);

  // Uses Boost's gzip interface to compress the response's body.
  // The response's original body is overwritten with the compressed version.
  // The "Content-Encoding" header is added with the value "gzip".
  void ApplyGzip(); 

private:  
  using Headers = std::vector<std::pair<std::string, std::string>>;
  Headers headers_;
  std::string body_;
  ResponseCode response_code_;
};


#endif //HTTP_RESPONSE_HPP

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <memory>
#include <vector>
#include <boost/asio.hpp>
#include "header.hpp"

const int MAX_REQUEST_SIZE = 8192;

namespace http {
  namespace server {
    
    class Request {
     public:

      static std::unique_ptr<Request> Parse(const std::string& raw_request);

      std::string raw_request() const;
      std::string method() const;
      std::string uri() const;
      std::string version() const;
      std::string body() const;
      
      using Headers = std::vector<std::pair<std::string, std::string>>;
      Headers headers() const;

	void set_raw_request(std::string raw_request);
	void set_method(std::string method);
	void set_uri(std::string uri);
	void set_version(std::string version);
	void set_body(std::string body);
	void set_headers(Headers headers);

    private:

      std::string raw_request_;
      std::string method_;
      std::string uri_;
      std::string version_;
      std::string body_;
      Headers headers_;
    };
    
  } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HPP

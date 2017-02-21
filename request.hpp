#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "header.hpp"

const int MAX_REQUEST_SIZE = 8192;

namespace http {
  namespace server {

    // struct request
    // {
    //   char content[MAX_REQUEST_SIZE];
    //   size_t length;
    //   std::string method;
    //   std::string uri;
    //   std::vector<header> headers;
    //   std::string base;

    // };

    class Request {
      std::string rawReqest;
      std::string method;
      std::string uri;
      std::string version;

      std::string body;

     public:
      static unique_ptr<Request> Parse(const std::string& raw_request);

      std::string raw_request() const;
      std::string method() const;
      std::string uri() const;
      std::string version() const;

      // using Headers = std::vector<std::pair<std::string, std::string>>;
      // Headers headers() const;

      //std::string body() const;
    };
    
  } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HPP

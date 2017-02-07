#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "header.hpp"

const int MAX_REQUEST_SIZE = 8192;

namespace http {
  namespace server {

    struct request
    {
      char content[MAX_REQUEST_SIZE];
      size_t length;
      std::string method;
      std::string uri;
      std::vector<header> headers;
      std::string base;

    };
    
  } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HPP

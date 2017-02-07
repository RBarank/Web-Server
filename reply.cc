//Based off http://www.boost.org/doc/libs/1_62_0/doc/html/boost_asio/example/cpp11/http/server/reply.cpp

#include "reply.hpp"
#include <string>

namespace http {
namespace server {

namespace status_strings {

const std::string ok =
  "HTTP/1.1 200 OK\r\n";
const std::string moved_permanently =
  "HTTP/1.1 301 Moved Permanently\r\n";
const std::string bad_request =
  "HTTP/1.1 400 Bad Request\r\n";
const std::string unauthorized =
  "HTTP/1.1 401 Unauthorized\r\n";
const std::string forbidden =
  "HTTP/1.1 403 Forbidden\r\n";
const std::string not_found =
  "HTTP/1.1 404 Not Found\r\n";
const std::string internal_server_error =
  "HTTP/1.1 500 Internal Server Error\r\n";

boost::asio::const_buffer to_buffer(reply::status_type status)
{
  switch (status)
  {
  case reply::ok:
    return boost::asio::buffer(ok);
  case reply::moved_permanently:
    return boost::asio::buffer(moved_permanently);
  case reply::bad_request:
    return boost::asio::buffer(bad_request);
  case reply::unauthorized:
    return boost::asio::buffer(unauthorized);
  case reply::forbidden:
    return boost::asio::buffer(forbidden);
  case reply::not_found:
    return boost::asio::buffer(not_found);
  default:
    return boost::asio::buffer(internal_server_error);
  }
}

} 

namespace misc_strings {

const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

} // namespace misc_strings

std::vector<boost::asio::const_buffer> reply::to_buffers()
{
  std::vector<boost::asio::const_buffer> buffers;
  buffers.push_back(status_strings::to_buffer(status));
  for (std::size_t i = 0; i < headers.size(); ++i)
  {
    header& h = headers[i];
    buffers.push_back(boost::asio::buffer(h.name));
    buffers.push_back(boost::asio::buffer(misc_strings::name_value_separator));
    buffers.push_back(boost::asio::buffer(h.value));
    buffers.push_back(boost::asio::buffer(misc_strings::crlf));
  }
  buffers.push_back(boost::asio::buffer(misc_strings::crlf));
  buffers.push_back(boost::asio::buffer(content));
  return buffers;
}



} // namespace server
} // namespace http
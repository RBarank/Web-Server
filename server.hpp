
#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include "config_parser.h"
#include "request_handler.hpp"

#include <boost/asio.hpp>
#include <string>
#include <unordered_map>

namespace http {
namespace server {

/// The top-level class of the HTTP server.
class server
{
public:
  server(const server&) = delete;
  server& operator=(const server&) = delete;

  /// Construct the server to listen on the specified TCP address and port, and
  /// serve up files from the given directory.
  explicit server(const std::string& address, const NginxConfig& config);

  // Get Server configuration information from the config
  bool get_config_info(const NginxConfig& config);

  /// Run the server's io_service loop.
  void run();


private:
  /// Perform an asynchronous accept operation.
  void do_accept();

  /// Wait for a request to stop the server.
  // void do_await_stop();

  /// The io_service used to perform asynchronous operations.
  boost::asio::io_service io_service_;

  /// Acceptor used to listen for incoming connections.
  boost::asio::ip::tcp::acceptor acceptor_;

  /// The next socket to be accepted.
  boost::asio::ip::tcp::socket socket_;

  int portno_;
  // TODO: make this a map to request handlers
  //std::unordered_map<std::string, std::unique_ptr<RequestHandler>> uri_to_handler_map;
  std::unordered_map<std::string, RequestHandler*> uri_to_handler_map;
};

} // namespace server
} // namespace http

#endif // HTTP_SERVER_HPP

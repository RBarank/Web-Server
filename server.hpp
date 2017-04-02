
#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include "config_parser.hpp"
#include "request_handler.hpp"
#include <vector>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>
#include <unordered_map>


/// The top-level class of the HTTP server.
class Server
{
public:
  Server(const Server&) = delete;
  Server& operator=(const Server&) = delete;
  
  /// Construct the Server to listen on the specified TCP address and port, and
  /// serve up files from the given directory.
  explicit Server(const std::string& address, const NginxConfig& config);
  
  // Get Server configuration information from the Nginx config
  bool GetConfigInfo(const NginxConfig& config);
  
  /// Run the Server's io_service loop.
  void Run();
    
  void Kill();
    
private:
  /// Perform an asynchronous accept operation.
  void DoAccept();
  
  void SetThreads(const NginxConfig& config);

  /// The io_service used to perform asynchronous operations.
  boost::asio::io_service io_service_;

  /// Acceptor used to listen for incoming connections.
  boost::asio::ip::tcp::acceptor acceptor_;
  
  /// The next socket to be accepted.
  boost::asio::ip::tcp::socket socket_;

  int port_number_;
  std::unordered_map<std::string, RequestHandler*> uri_to_handler_map_;
  std::unordered_map<std::string, std::string> uri_to_handler_name_;
  int num_threads_;
  std::vector<std::shared_ptr<std::thread>> threads_;
  
};

#endif // HTTP_SERVER_HPP

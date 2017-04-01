
#ifndef HTTP_CONNECTION_HPP
#define HTTP_CONNECTION_HPP

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "response.hpp"
#include "request.hpp"
#include "request_handler.hpp"
#include "echo_handler.hpp"
#include "static_handler.hpp"
#include <unordered_map>


//const int MAX_REQUEST_SIZE = 8192; // already defined in request.hpp

/// Represents a single connection from a client.
class Connection
  : public std::enable_shared_from_this<Connection>  // this allows us to use in the Connection class's methods the "shared_from_this()" 
{                                                    // function, which returns a shared_ptr to the instance of Connection
public:
  Connection(const Connection&) = delete;
  Connection& operator=(const Connection&) = delete;
  RequestHandler* GetRequestHandler(const std::string& path);
  /// Construct a Connection with the given socket.
  explicit Connection(boost::asio::ip::tcp::socket socket, const std::unordered_map<std::string, 
		      RequestHandler*>& path_map, const std::unordered_map<std::string, std::string>& name_map);
      
  /// Start the first asynchronous operation for the Connection.
  void Start();
      
  /// Stop all asynchronous operations associated with the Connection.
  void Stop();
      
  //boost::asio::ip::tcp::socket getSocket() {return socket_;}
      
private:
  /// Perform an asynchronous read operation.
  void DoRead();
  
  /// Perform an asynchronous write operation.
  void DoWrite();
  
  void HandleRead();
  
  void ParseRequest();
  
  /// Socket for the Connection.
  boost::asio::ip::tcp::socket socket_;
  
  std::unordered_map<std::string, RequestHandler*> path_map_;
  std::unordered_map<std::string, std::string> name_map_;
        
  /// Buffer for incoming data.
  char request_buffer_[MAX_REQUEST_SIZE];
  
  boost::asio::streambuf buffer_;
};

typedef std::shared_ptr<Connection> connection_ptr;


#endif // HTTP_CONNECTION_HPP


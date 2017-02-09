
#ifndef HTTP_CONNECTION_HPP
#define HTTP_CONNECTION_HPP

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "reply.hpp"
#include "request.hpp"
#include <unordered_map>


//const int MAX_REQUEST_SIZE = 8192;

namespace http {
  namespace server {

    class connection_manager;

    /// Represents a single connection from a client.
    class connection
      : public std::enable_shared_from_this<connection>
    {
    public:
      connection(const connection&) = delete;
      connection& operator=(const connection&) = delete;
      
      /// Construct a connection with the given socket.
      explicit connection(boost::asio::ip::tcp::socket socket, const std::unordered_map<std::string, std::string>& pathMap);
      
      /// Start the first asynchronous operation for the connection.
      void start();
      
      /// Stop all asynchronous operations associated with the connection.
      void stop();
      
      //boost::asio::ip::tcp::socket getSocket() {return socket_;}
      
    private:
      /// Perform an asynchronous read operation.
      void do_read();
      
      /// Perform an asynchronous write operation.
      void do_write();

      
      void handle_request();
      void do_echo();
      void do_static();

      
      /// Socket for the connection.
      boost::asio::ip::tcp::socket socket_;

      std::unordered_map<std::string, std::string> pathMap_;
      
      /// Buffer for incoming data.
      //char request_buffer[MAX_REQUEST_SIZE];
      
      /// The reply to be sent back to the client.
      reply reply_;

      request request_;
    };

    typedef std::shared_ptr<connection> connection_ptr;

  } // namespace server
} // namespace http

#endif // HTTP_CONNECTION_HPP


#include "gtest/gtest.h"
#include "request.hpp"
#include <string>

namespace http{
  namespace server{


TEST(RequestTest, EmptyRequest) 
{
  Request empty_request;
  EXPECT_EQ(empty_request.raw_request(), "");
  EXPECT_EQ(empty_request.method(), "");
  EXPECT_EQ(empty_request.uri(), "");
  EXPECT_EQ(empty_request.body(), "");
  EXPECT_EQ(empty_request.version(), "");
  EXPECT_EQ(empty_request.headers().size(), 0);
}

TEST(RequestTest2, ParseRequest) 
{
  std::string echo_request = "GET /echo/hello.html HTTP/1.1\r\n";
  echo_request += "Host: localhost:3000\r\n";
  echo_request += "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:50.0) Gecko/20100101 Firefox/50.0\r\n";
  echo_request += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
  echo_request += "Accept-Language: en-US,en;q=0.5\r\n";
  echo_request += "Accept-Encoding: gzip, deflate\r\n";
  echo_request += "Connection: keep-alive\r\n";
  echo_request += "Upgrade-Insecure-Requests: 1\r\n";
  echo_request += "\r\n";
  echo_request += "This is a test body.";

  std::unique_ptr<Request> request = Request::Parse(echo_request);
  
  EXPECT_EQ(request->raw_request(), echo_request);
  EXPECT_EQ(request->method(), "GET");
  EXPECT_EQ(request->uri(), "/echo/hello.html");
  EXPECT_EQ(request->body(), "This is a test body.");
  EXPECT_EQ(request->version(), "HTTP/1.1");
  EXPECT_EQ(request->headers().size(), 7);
}
    
TEST(RequestTest, AcceptGzip) 
{
  std::string echo_request = "GET /echo/hello.html HTTP/1.1\r\n";
  echo_request += "Accept-Encoding: gzip, deflate\r\n";

  std::unique_ptr<Request> request = Request::Parse(echo_request);
  
  EXPECT_TRUE(request->accept_gzip());
}

TEST(RequestTest, get_header) 
{
  std::string echo_request = "GET /echo/hello.html HTTP/1.1\r\n";
  echo_request += "Accept-Encoding: gzip, deflate\r\n";

  std::unique_ptr<Request> request = Request::Parse(echo_request);
  
  EXPECT_EQ(request->get_header("Accept-Encoding"), "gzip, deflate");
}


  } // namespace server
} // namespace http

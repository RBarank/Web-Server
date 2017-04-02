#include "gtest/gtest.h"
#include "request.hpp"
#include <string>


TEST(RequestTest, EmptyRequest) 
{
  Request empty_request;
  EXPECT_EQ(empty_request.GetRawRequest(), "");
  EXPECT_EQ(empty_request.GetMethod(), "");
  EXPECT_EQ(empty_request.GetUri(), "");
  EXPECT_EQ(empty_request.GetBody(), "");
  EXPECT_EQ(empty_request.GetVersion(), "");
  EXPECT_EQ(empty_request.GetHeaders().size(), 0);
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
  
  EXPECT_EQ(request->GetRawRequest(), echo_request);
  EXPECT_EQ(request->GetMethod(), "GET");
  EXPECT_EQ(request->GetUri(), "/echo/hello.html");
  EXPECT_EQ(request->GetBody(), "This is a test body.");
  EXPECT_EQ(request->GetVersion(), "HTTP/1.1");
  EXPECT_EQ(request->GetHeaders().size(), 7);
}
    
TEST(RequestTest, AcceptsGzip) 
{
  std::string echo_request = "GET /echo/hello.html HTTP/1.1\r\n";
  echo_request += "Accept-Encoding: gzip, deflate\r\n";

  std::unique_ptr<Request> request = Request::Parse(echo_request);
  
  EXPECT_TRUE(request->AcceptsGzip());
}

TEST(RequestTest, GetHeaderByName) 
{
  std::string echo_request = "GET /echo/hello.html HTTP/1.1\r\n";
  echo_request += "Accept-Encoding: gzip, deflate\r\n";

  std::unique_ptr<Request> request = Request::Parse(echo_request);
  
  EXPECT_EQ(request->GetHeaderByName("Accept-Encoding"), "gzip, deflate");
}

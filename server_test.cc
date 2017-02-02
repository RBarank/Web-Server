#include "gtest/gtest.h"
#include "server.hpp"
#include <string>

TEST(ServerTest, BadPortNo) 
{
  std::string link = "127.0.0.1", port = "999998080";
  http::server::server test_server(link, port);

  EXPECT_FALSE(test_server.isValidServer());
}


TEST(ServerTest, BadAddr) 
{
  std::string link = ".0.0.1", port = "8080";
  http::server::server test_server(link, port);

  EXPECT_FALSE(test_server.isValidServer());
}

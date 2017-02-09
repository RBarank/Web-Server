#include "gtest/gtest.h"
#include "server.hpp"
#include <string>

std::unordered_map<std::string, std::string> test_map;

TEST(ServerTest, BadAddr) 
{
  EXPECT_ANY_THROW(http::server::server test_server(".0.0.1", "8000", test_map));
  EXPECT_ANY_THROW(http::server::server test_server("..0.1", "8000", test_map));
  EXPECT_ANY_THROW(http::server::server test_server("999.0.0.1", "8000", test_map));
  EXPECT_ANY_THROW(http::server::server test_server("1234567.0.", "8000", test_map));
}

TEST(ServerTest, BadPortNo) 
{
  EXPECT_ANY_THROW(http::server::server test_server("127.0.0.1", "blah", test_map));
  EXPECT_ANY_THROW(http::server::server test_server("127.0.0.1", "", test_map));
  EXPECT_ANY_THROW(http::server::server test_server("127.0.0.1", "-98", test_map));
}

TEST(ServerTest, GoodConfigs) 
{
  EXPECT_NO_THROW(http::server::server test_server("127.0.0.1", "8080", test_map));
  EXPECT_NO_THROW(http::server::server test_server("127.0.0.1", "3033", test_map));
}


#include "gtest/gtest.h"
#include "server.hpp"
#include <string>


TEST(ServerTest, BadAddr) 
{
  EXPECT_ANY_THROW(http::server::server test_server(".0.0.1", "8000"));
  EXPECT_ANY_THROW(http::server::server test_server("..0.1", "8000"));
  EXPECT_ANY_THROW(http::server::server test_server("999.0.0.1", "8000"));
  EXPECT_ANY_THROW(http::server::server test_server("1234567.0.", "8000"));
}

TEST(ServerTest, BadPortNo) 
{
  EXPECT_ANY_THROW(http::server::server test_server("127.0.0.1", "blah"));
  EXPECT_ANY_THROW(http::server::server test_server("127.0.0.1", ""));
  EXPECT_ANY_THROW(http::server::server test_server("127.0.0.1", "-98"));

  http::server::server test_server("127.0.0.1", "99999999");
  EXPECT_FALSE(test_server.isValid());
}

TEST(ServerTest, GoodConfigs) 
{
  EXPECT_NO_THROW(http::server::server test_server("127.0.0.1", "8080"));
  EXPECT_NO_THROW(http::server::server test_server("127.0.0.127", "3033"));
  
  http::server::server test_server("127.0.0.1", "8080");  
  EXPECT_TRUE(test_server.isValid());
}

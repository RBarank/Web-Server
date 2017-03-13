#include "gtest/gtest.h"
#include "server.hpp"
#include "config_parser.h"
#include <string>

std::unordered_map<std::string, std::string> test_map;

NginxConfig retGoodConfig()
{
    NginxConfigParser parser;
    NginxConfig test_config;
    parser.Parse("config_file", &test_config);
    return test_config;
}

TEST(ServerTest, BadAddrAndEmptyConfig)
{
  NginxConfig empty_config;

  EXPECT_ANY_THROW(http::server::server test_server(".0.0.1", empty_config));
  EXPECT_ANY_THROW(http::server::server test_server("..0.1", empty_config));
  EXPECT_ANY_THROW(http::server::server test_server("999.0.0.1", empty_config));
  EXPECT_ANY_THROW(http::server::server test_server("1234567.0.", empty_config));
}

TEST(ServerTest, GoodAddrAndEmptyConfig) 
{
  NginxConfig empty_config;

  EXPECT_ANY_THROW(http::server::server test_server("127.0.0.1", empty_config));
  EXPECT_ANY_THROW(http::server::server test_server("127.0.0.1", empty_config));
  EXPECT_ANY_THROW(http::server::server test_server("127.0.0.1", empty_config));
}

TEST(ServerTest, NotGoodConfigs)
{
    NginxConfig test_config = retGoodConfig();
    EXPECT_NO_THROW(http::server::server test_server("127.0.0.1", test_config));
    http::server::server test("0.0.0.0", test_config);
    test.kill();
}

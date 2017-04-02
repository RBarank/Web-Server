#include "gtest/gtest.h"
#include "server.hpp"
#include "config_parser.hpp"
#include <string>

std::unordered_map<std::string, std::string> test_map;

NginxConfig RetGoodConfig()
{
  NginxConfigParser parser;
  NginxConfig test_config;
  parser.Parse("config_file", &test_config);
  return test_config;
}

TEST(ServerTest, GoodConfigs)
{
  NginxConfig test_config = RetGoodConfig();
  EXPECT_NO_THROW(Server test_server("127.0.0.1", test_config));
  Server test("0.0.0.0", test_config);
  test.Kill();
}

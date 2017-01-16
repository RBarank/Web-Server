#include "gtest/gtest.h"
#include "config_parser.h"

// The test case below is the one we were given.
TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("example_config", &out_config);

  EXPECT_TRUE(success);
}

// The test cases below here are the ones I added.
TEST(NginxConfigParserTest, ConfigFileErrors)
{
  NginxConfigParser parser;
  NginxConfig out_config;

  EXPECT_FALSE(parser.Parse("does_not_exist_config", &out_config));
  EXPECT_FALSE(parser.Parse("", &out_config));
  EXPECT_TRUE(parser.Parse("server { listen 80; }", &out_config));
}

TEST(NginxConfigToStringTest, SimpleText)
{
  NginxConfigStatement statement;
  statement.tokens_.push_back("This");
  statement.tokens_.push_back("is");
  statement.tokens_.push_back("a");
  statement.tokens_.push_back("test");

  EXPECT_EQ("This is a test;\n", statement.ToString(0));
}

// Test various strings that shouldn't be allowed like instead of "listen    80" write
// "80    listen" or "asdasd asdasda"
/*
TEST(NginxParseTokenTest, Simple1)
{
  NginxConfigParser parser;
  NginxConfig out_config;

  // this test has the wrong return type, need tp fix it
  EXPECT_TRUE(parser.ParseToken("server { listen 80;}"));


}
*/

#include "gtest/gtest.h"
#include "config_parser.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

// This is the example test case we were given
/*TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("example_config", &out_config);

  EXPECT_TRUE(success);
  }*/


// The test cases below here are the ones I added.

TEST(NginxConfigParserValid, ValidConfig)
{
  NginxConfigParser parser;
  NginxConfig out_config;

  std::stringstream buf("server { listen 80; server_name foo.com; root /home/ubuntu/sites/foo/; }");
  EXPECT_TRUE(parser.Parse(&buf, &out_config));

  buf.str("server { listen 80; }");
  buf.clear();
  EXPECT_TRUE(parser.Parse(&buf, &out_config));
  
  buf.str("server { server_name foo.com; root /home/ubuntu/sites/foo; }");
  buf.clear();
  EXPECT_TRUE(parser.Parse(&buf, &out_config));
  
}

TEST(NginxConfigParserInvalid, BadBrackets)
{
  NginxConfigParser parser;
  NginxConfig out_config;

  std::stringstream buf("server {{ listen 80; server_name foo.com; root /home/ubuntu/sites/foo/; ");
  EXPECT_FALSE(parser.Parse(&buf, &out_config));

  buf.str("server { listen 80; server_name foo.com; root /home/ubuntu/sites/foo/; ");
  buf.clear();
  EXPECT_FALSE(parser.Parse(&buf, &out_config));

  buf.str("server listen 80; server_name foo.com; root /home/ubuntu/sites/foo/; }");
  buf.clear();
  EXPECT_FALSE(parser.Parse(&buf, &out_config));

  buf.str("server {}");
  buf.clear();
  EXPECT_FALSE(parser.Parse(&buf, &out_config));
}

TEST(NginxConfigParserInvalid, BadValues)
{
  NginxConfigParser parser;
  NginxConfig out_config;

  std::stringstream buf("server { listen eighty; server_name foo.com; root /home/ubuntu/sites/foo/; }");
  EXPECT_FALSE(parser.Parse(&buf, &out_config));

  buf.str("server { listen 80; server_name 12345; root /home/ubuntu/sites/foo/; }");
  buf.clear();
  EXPECT_FALSE(parser.Parse(&buf, &out_config));
}

TEST(NginxConfigParserInvalid, BadSemicolons)
{
  NginxConfigParser parser;
  NginxConfig out_config;

  std::stringstream buf("server { listen 80 server_name foo.com; root /home/ubuntu/sites/foo/; }");
  EXPECT_FALSE(parser.Parse(&buf, &out_config));

  buf.str("server ;{ listen 80; server_name foo.com; root /home/ubuntu/sites/foo/; }");
  buf.clear();
  EXPECT_FALSE(parser.Parse(&buf, &out_config));

  buf.str("server { listen 80;; server_name foo.com; root /home/ubuntu/sites/foo/; }");
  buf.clear();
  EXPECT_FALSE(parser.Parse(&buf, &out_config));

  buf.str("server { listen; 80 server_name foo.com; root /home/ubuntu/sites/foo/; }");
  buf.clear();
  EXPECT_FALSE(parser.Parse(&buf, &out_config));

}

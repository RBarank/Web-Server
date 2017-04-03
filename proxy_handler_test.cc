#include "gtest/gtest.h"
#include "proxy_handler.hpp"
#include <vector>
#include "config_parser.hpp"
#include "request_handler.hpp"
#include "response.hpp"
#include "request.hpp"


//the gibberish on the command line when testing HandleRequest function is the content of the website dumped to the terminal 

ProxyHandler proxy_handler;

TEST(ProxyHandlerInit, NoHostName) 
{
  ProxyHandler handler;
  std::string uri_prefix = "/proxy1";
  NginxConfig config;
  
  config.statements_.emplace_back(new NginxConfigStatement);
  config.statements_.back().get()->tokens_.push_back("port");
  config.statements_.back().get()->tokens_.push_back("80");
  
  EXPECT_EQ(handler.Init(uri_prefix, config), 
	    RequestHandler::NOT_OK);
}

TEST(ProxyHandlerInit, NoPort) 
{
  ProxyHandler handler;
  std::string uri_prefix = "/proxy1";
  NginxConfig config;
  
  config.statements_.emplace_back(new NginxConfigStatement);
  config.statements_.back().get()->tokens_.push_back("host");
  config.statements_.back().get()->tokens_.push_back("www.ucla.edu");
  
  EXPECT_EQ(handler.Init(uri_prefix, config), 
	    RequestHandler::NOT_OK);
}

TEST(ProxyHandlerInit, BadPortNum) 
{
  ProxyHandler handler;
  std::string uri_prefix = "/proxy1";
  NginxConfig config;
  
  config.statements_.emplace_back(new NginxConfigStatement);
  config.statements_.back().get()->tokens_.push_back("port");
  config.statements_.back().get()->tokens_.push_back("not a valid number");
  
  EXPECT_EQ(handler.Init(uri_prefix, config), 
	    RequestHandler::NOT_OK);
}

TEST(ProxyHandlerInit, EmptyConfig) 
{
  ProxyHandler handler;
  std::string uri_prefix = "/proxy1";
  NginxConfig config;
  EXPECT_EQ(handler.Init(uri_prefix, config), 
	    RequestHandler::NOT_OK);
		
}

//added a fixture for common variables 
class ProxyHandlerTest:public::testing::Test
{
protected:
  bool parseConfig(const std::string config_string)
  {
    std::stringstream config_stream(config_string);
    return parser.Parse(&config_stream, &out_config);
  }
  NginxConfigParser parser;
  NginxConfig out_config;
};

//test the init function, check if variables are set correctly
TEST_F(ProxyHandlerTest, INIT) 
{
  parseConfig("remote_host http://www.ucla.edu;");
  auto init_status = proxy_handler.Init("/", out_config);
  EXPECT_EQ(init_status, RequestHandler::Status::NOT_OK);
}

//set status as NOT_OK if there's no protocol in config
TEST_F(ProxyHandlerTest, NoProtocol)
{
  parseConfig("remote_host www.ucla.edu;");
  auto init_status = proxy_handler.Init("/", out_config);
  EXPECT_EQ(init_status, RequestHandler::Status::NOT_OK);
}

//illegal config with wrong keyword
TEST_F(ProxyHandlerTest, IllegalConfig)
{
  parseConfig("host http://www.ucla.edu;");
  auto init_status = proxy_handler.Init("/", out_config);
  EXPECT_EQ(init_status, RequestHandler::Status::NOT_OK);
}

//illegal config with too many statements
TEST_F(ProxyHandlerTest, TooManyStatements)
{
  parseConfig("remote_host http://www.ucla.edu; remote_host2 http://www.google.com");
  auto init_status = proxy_handler.Init("/", out_config);
  EXPECT_EQ(init_status, RequestHandler::Status::NOT_OK);
}

//test HandleRequest function
//this unit test might fail if there is no or has weak internet connection
TEST_F(ProxyHandlerTest, HandleRequest)
{	
  Response response;
  std::string raw_request = "GET / HTTP/1.1\r\n\r\n";
  std::unique_ptr<Request> req(new Request);
  req->SetRawRequest(raw_request);
  req->SetMethod("GET");
  req->SetUri("/");
  req->SetVersion("HTTP/1.1");
  
  parseConfig("remote_host http://www.ucla.edu;");
  
  EXPECT_EQ(out_config.statements_[0]->tokens_[1],"http://www.ucla.edu");
  EXPECT_EQ(out_config.statements_[0]->tokens_[0],"remote_host");
  auto init_status = proxy_handler.Init("/", out_config);
  EXPECT_EQ(init_status, RequestHandler::Status::NOT_OK);
}

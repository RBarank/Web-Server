#include "gtest/gtest.h"
#include "proxy_handler.hpp"
#include <vector>
#include "config_parser.h"
#include "request_handler.hpp"
#include "response.hpp"
#include "request.hpp"


//the gibberish on the command line when testing HandleRequest function is the content of the website dumped to the terminal 

namespace http {
    namespace server{

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
			ProxyHandler proxy_handler;
		};
        
		//test the init function, check if variables are set correctly
		TEST_F(ProxyHandlerTest, INIT) 
		{
			parseConfig("remote_host http://www.ucla.edu;");
			auto init_status = proxy_handler.Init("/", out_config);
			EXPECT_EQ(init_status, RequestHandler::Status::OK);
			EXPECT_EQ(proxy_handler.getPrefix(), "/");
			EXPECT_EQ(proxy_handler.getWholeURL(),"http://www.ucla.edu"); 
			EXPECT_EQ(proxy_handler.getProtocol(),"http"); 
			EXPECT_EQ(proxy_handler.getHostURL(),"www.ucla.edu"); 
			EXPECT_EQ(proxy_handler.getPath(),""); 
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
			parseConfig("remote_host http://www.ucla.edu;remote_host2 http://www.google.com");
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
			req->set_raw_request(raw_request);
			req->set_method("GET");
			req->set_uri("/");
			req->set_version("HTTP/1.1");

			parseConfig("remote_host http://www.ucla.edu;");

			EXPECT_EQ(out_config.statements_[0]->tokens_[1],"http://www.ucla.edu");
			EXPECT_EQ(out_config.statements_[0]->tokens_[0],"remote_host");
			auto init_status = proxy_handler.Init("/", out_config);
			EXPECT_EQ(init_status, RequestHandler::Status::OK);

			auto status = proxy_handler.HandleRequest(*req, &response);
			EXPECT_EQ(status, RequestHandler::Status::OK);	
		}
   }//server
}//http

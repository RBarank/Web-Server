#include "gtest/gtest.h"
#include "static_handler.hpp"
#include <vector>
#include "config_parser.h"

namespace http {
    namespace server{
        
        std::string ret_bufferString(std::string type) {
            std::string bufferString = "";
            
            bufferString+= "GET /";
            bufferString+= type;
            bufferString+= " HTTP/1.1\n";
            bufferString+= "Host: localhost:3000\n";
            bufferString+= "Connection: keep-alive\n";
            bufferString+= "Cache-Control: max-age=0\n";

            bufferString+= "Upgrade-Insecure-Requests: 1\n";
            bufferString+= "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36\n";
            bufferString+= "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\n";
            bufferString+= "Accept-Encoding: gzip, deflate, sdch, br\n";
            bufferString+= "Accept-Language: en-US,en;q=0.8\n\n\n";
            
            return bufferString;
        }
        
        
        TEST(StaticHandler, INIT) {
            StaticHandler test;
            NginxConfig config;
            ASSERT_TRUE(test.Init("", config) == RequestHandler::Status::OK);
        }
        
        
        TEST(StaticHandler, WrongHandleRequestTests) {
            StaticHandler test;
            NginxConfig config;
            ASSERT_TRUE(test.Init("", config) == RequestHandler::Status::OK);
            Request request_;
            Response res_;
            ASSERT_TRUE(test.HandleRequest(request_, &res_) == RequestHandler::Status::NOT_OK);
            
            std::vector<std::string> testStrings {"echo", "/static/popo", "not%f" , "not_%%%%found" , "static/test.jpg" , "/.."};
            for (int i = 0; i < testStrings.size(); i++)
            {
                std::string bufferString = ret_bufferString(testStrings[i]);
                std::unique_ptr<Request> currentRequest(Request::Parse(bufferString));
                ASSERT_TRUE(test.HandleRequest(*currentRequest, &res_) == RequestHandler::Status::NOT_OK);
            }
        }
        
        
        TEST(StaticHandler, RightHandleRequestTests) {
            StaticHandler test;
            NginxConfigParser config_parser;
            NginxConfig config;
            config_parser.Parse("test_file/static_test", &config);
            
            Response res_;
            ASSERT_TRUE(test.Init("", config) == RequestHandler::Status::OK);
            
            std::string bufferString = ret_bufferString("static/test.jpg");
            std::unique_ptr<Request> currentRequest(Request::Parse(bufferString));
            
            ASSERT_TRUE(test.HandleRequest(*currentRequest, &res_) == RequestHandler::Status::OK);
        }
    }
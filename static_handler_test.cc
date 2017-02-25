#include "gtest/gtest.h"
#include "static_handler.hpp"

namespace http {
    namespace server{
        
        TEST(StaticHandler, INIT) {
            StaticHandler test;
            NginxConfig config;
            ASSERT_TRUE(test.Init("", config) == RequestHandler::Status::OK);
        }
        
        TEST(StaticHandler, HandleRequestTests) {
            StaticHandler test;
            NginxConfig config;
            ASSERT_TRUE(test.Init("", config) == RequestHandler::Status::OK);
            Request request_;
            ASSERT_TRUE(test.HandleRequest(request_, &res_) == RequestHandler::Status::NOT_OK);
        }
    }
}
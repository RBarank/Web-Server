#include "gtest/gtest.h"
#include "../src/echo_handler.hpp"
#include "../src/request.hpp"

namespace http {
    namespace server{
        
        TEST(EchoHandlerTest, all) {
            EchoHandler test;
            NginxConfig config;
            ASSERT_TRUE(test.Init("", config) == RequestHandler::Status::OK);
            Request req_;
            Response res_;
            ASSERT_TRUE(test.HandleRequest(req_, &res_) == RequestHandler::Status::OK);
        }
    }
}

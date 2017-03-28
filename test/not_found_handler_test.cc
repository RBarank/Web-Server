#include "gtest/gtest.h"
#include "not_found_handler.hpp"


namespace http {
    namespace server{
        
        TEST(NotFoundHandler404, all) {
            NotFoundHandler test;
            NginxConfig config;
            ASSERT_TRUE(test.Init("", config) == RequestHandler::Status::OK);
            Request req_;
            Response res_;
            ASSERT_TRUE(test.HandleRequest(req_, &res_) == RequestHandler::Status::OK);
        }
        
    }
}

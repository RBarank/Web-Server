#include "gtest/gtest.h"
#include "echo_handler.hpp"
#include "request.hpp"

TEST(EchoHandlerTest, all) 
{
  EchoHandler test;
  NginxConfig config;
  ASSERT_TRUE(test.Init("", config) == RequestHandler::Status::OK);
  Request req_;
  Response res_;
  ASSERT_TRUE(test.HandleRequest(req_, &res_) == RequestHandler::Status::OK);
}

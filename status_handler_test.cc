#include "gtest/gtest.h"
#include "status_handler.hpp"
#include <string>
#include <vector>

TEST(statusHandler, all) 
{
  StatusHandler test;
  NginxConfig config;
  ASSERT_TRUE(test.Init("", config) == RequestHandler::Status::OK);
  Request req_;
  Response res_;
  ASSERT_TRUE(test.HandleRequest(req_, &res_) == RequestHandler::Status::OK);
}

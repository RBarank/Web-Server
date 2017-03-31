#include "gtest/gtest.h"
#include "server_info.hpp"
#include <string>
#include <vector>
#include "response.hpp"


TEST(ServerInfoTest, all) 
{
  EXPECT_EQ(ServerInfo::getInstance().get_number_of_requests() , 0);
  ServerInfo::getInstance().append_request("a", Response::accepted);
  EXPECT_EQ(ServerInfo::getInstance().get_number_of_requests() , 1);
  ServerInfo::getInstance().append_request("a", Response::ok);
  EXPECT_EQ(ServerInfo::getInstance().get_number_of_requests() , 2);
  
  ServerInfo::getInstance().append_handler("echo", "/root");
  EXPECT_EQ(ServerInfo::getInstance().get_number_of_requests() , 2);
  
  std::vector<RequestInfo> requests = ServerInfo::getInstance().ret_request_info();
  
  for (size_t i = 0; i < requests.size(); i++)
    {
      EXPECT_EQ(requests[i].url, "a");
      if (i == 0)
        {
	  EXPECT_EQ(requests[i].rc, Response::accepted);
        }
      else
        {
	  EXPECT_EQ(requests[i].rc, Response::ok);
        }
    }
  
  std::vector<HandlerInfo> handlers = ServerInfo::getInstance().ret_handler_info();
  
  for (size_t i = 0; i < handlers.size(); i++)
    {
      EXPECT_EQ(handlers[i].type_of_handler, "echo");
      EXPECT_EQ(handlers[i].url_prefix, "/root");
    }
}

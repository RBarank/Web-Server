#include "gtest/gtest.h"
#include "server_info.hpp"
#include <string>
#include <vector>
#include "response.hpp"


TEST(ServerInfoTest, all) 
{
    EXPECT_EQ(http::server::ServerInfo::getInstance().get_number_of_requests() , 0);
    http::server::ServerInfo::getInstance().append_request("a", http::server::Response::accepted);
    EXPECT_EQ(http::server::ServerInfo::getInstance().get_number_of_requests() , 1);
    http::server::ServerInfo::getInstance().append_request("a", http::server::Response::ok);
    EXPECT_EQ(http::server::ServerInfo::getInstance().get_number_of_requests() , 2);
    
    http::server::ServerInfo::getInstance().append_handler("echo", "/root");
    EXPECT_EQ(http::server::ServerInfo::getInstance().get_number_of_requests() , 2);
    
    std::vector<http::server::RequestInfo> requests = http::server::ServerInfo::getInstance().ret_request_info();
    
    for (int i = 0; i < requests.size(); i++)
    {
        EXPECT_EQ(requests[i].url, "a");
        if (i == 0)
        {
            EXPECT_EQ(requests[i].rc, http::server::Response::accepted);
        }
        else
        {
            EXPECT_EQ(requests[i].rc, http::server::Response::ok);
        }
    }
    
    std::vector<http::server::HandlerInfo> handlers = http::server::ServerInfo::getInstance().ret_handler_info();
    
    for (int i = 0; i < handlers.size(); i++)
    {
        EXPECT_EQ(handlers[i].type_of_handler, "echo");
        EXPECT_EQ(handlers[i].url_prefix, "/root");
    }
}

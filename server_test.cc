#include "gtest/gtest.h"
#include "server.hpp"
#include <string>

TEST(ServerTest, InvalidPortNumber) {
    try {
        std::string link = "127.0.0.1", port = "436787";
        http::server::server test_server(link, port);
    }
    catch(boost::system::error_code &e) {
        EXPECT_EQ(e.message(), "Invalid argument");
    }
}

TEST(ServerTest, ConstrutorAnddoAccept) {
    try {
        std::string link = "127.0.0.1", port = "8080";
        http::server::server test_server(link, port);
    }
    catch(boost::system::error_code &e) {
        throw e.message();
    }
}


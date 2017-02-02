#include "gtest/gtest.h"
#include "server.hpp"
#include <string>

TEST(ServerTest, Construtor) {
    try {
        std::string link = "127.0.0.1", port = "8080";
        http::server::server test_server(link, port);
        test_server.run();
    }
    catch(boost::system::error_code &e) {
        throw e.message();
    }
}


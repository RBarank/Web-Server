#include "gtest/gtest.h"
#include "request_handler.hpp"
#include "echo_handler.hpp"
#include "static_handler.hpp"
#include <string>


TEST(request_handle_, URL)
{
    std::string echo_str = "/echo", empty = "";
    EXPECT_NO_THROW(http::server::request_handler::generateHandler(echo_str, empty));
}


TEST(request_handle_, static_)
{
    std::string static_str = "/static", root = "/test";
    EXPECT_NO_THROW(http::server::request_handler::generateHandler(static_str, root));
}


TEST(request_handle_, null_)
{
    std::string rnd_str = "LOL", empty = "";
    EXPECT_EQ(http::server::request_handler::generateHandler(rnd_str, empty),nullptr);
}

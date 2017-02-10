#include "gtest/gtest.h"
#include "request_handler.hpp"
#include "echo_handler.hpp"
#include "static_handler.hpp"
#include <string>


TEST(request_handle_constructor_and_rh_, URL)
{
    std::string echo_str = "/echo", empty = "";
    EXPECT_NO_THROW(http::server::request_handler::generateHandler(echo_str, empty));
}

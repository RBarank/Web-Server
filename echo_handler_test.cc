#include "gtest/gtest.h"
#include "echo_handler.hpp"
#include "request.hpp"
#include "reply.hpp"


TEST(echo_handle_, handle_request_)
{
    http::server::echo_handler echo_handler_;
    http::server::request request_;
    request_.content[0] = 'A';
    request_.content[0] = 'B';
    request_.content[0] = 'C';
    request_.length = 3;
    http::server::reply reply_;
    EXPECT_TRUE(echo_handler_.handle_request(request_, reply_));
}


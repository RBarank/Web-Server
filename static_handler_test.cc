#include "gtest/gtest.h"
#include "static_handler.hpp"
#include "request.hpp"
#include "reply.hpp"


TEST(static_handle_, almost_correct_request)
{
    http::server::static_handler static_handler_("/test_folder");
    http::server::request request_;
    request_.content[0] = 'A';
    request_.content[0] = 'B';
    request_.content[0] = 'C';
    request_.length = 3;
    request_.method = "GET";
    request_.uri = "/static/test.jpg";
    request_.base = "/static";
    http::server::reply reply_;
    EXPECT_TRUE(static_handler_.handle_request(request_, reply_));
}

TEST(static_handle_, index_html)
{
    http::server::static_handler static_handler_("/test_folder");
    http::server::request request_;
    request_.content[0] = 'A';
    request_.content[0] = 'B';
    request_.content[0] = 'C';
    request_.length = 3;
    request_.method = "GET";
    request_.uri = "/static/";
    request_.base = "/static";
    http::server::reply reply_;
    EXPECT_FALSE(static_handler_.handle_request(request_, reply_));
}

TEST(static_handle_, percent_error)
{
    http::server::static_handler static_handler_("/test_folder");
    http::server::request request_;
    request_.content[0] = 'A';
    request_.content[0] = 'B';
    request_.content[0] = 'C';
    request_.length = 3;
    request_.method = "GET";
    request_.uri = "/static/t+est.j%pg";
    request_.base = "/static";
    http::server::reply reply_;
    EXPECT_FALSE(static_handler_.handle_request(request_, reply_));
}


TEST(static_handle_, hex_error)
{
    http::server::static_handler static_handler_("/test_folder");
    http::server::request request_;
    request_.content[0] = 'A';
    request_.content[0] = 'B';
    request_.content[0] = 'C';
    request_.length = 3;
    request_.method = "GET";
    request_.uri = "/static/te%st.jpg";
    request_.base = "/static";
    http::server::reply reply_;
    EXPECT_FALSE(static_handler_.handle_request(request_, reply_));
}

TEST(static_handle_, empty_path)
{
    http::server::static_handler static_handler_("/test_folder");
    http::server::request request_;
    request_.content[0] = 'A';
    request_.content[0] = 'B';
    request_.content[0] = 'C';
    request_.length = 3;
    request_.method = "GET";
    request_.uri = "/static";
    request_.base = "/static";
    http::server::reply reply_;
    EXPECT_FALSE(static_handler_.handle_request(request_, reply_));
}

TEST(static_handle_, dot_before_slash)
{
    http::server::static_handler static_handler_("/test_folder");
    http::server::request request_;
    request_.content[0] = 'A';
    request_.content[0] = 'B';
    request_.content[0] = 'C';
    request_.length = 3;
    request_.method = "GET";
    request_.uri = "/static/te%st.jp/g";
    request_.base = "/static";
    http::server::reply reply_;
    EXPECT_FALSE(static_handler_.handle_request(request_, reply_));
}



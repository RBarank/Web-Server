#include "gtest/gtest.h"
#include "connection.hpp"
#include <boost/asio.hpp>

boost::asio::io_service io_service_;
boost::asio::ip::tcp::socket socket_(io_service_);

void startConnection(http::server::connection& test_connection)
{
    test_connection.start();
}

void stopConnection(http::server::connection& test_connection)
{
    test_connection.stop();
}


TEST(ConnectionTest, constructor_tests) {
    http::server::connection test_connection(std::move(socket_));
    EXPECT_FALSE(socket_.is_open());
    EXPECT_ANY_THROW(startConnection(test_connection));
    EXPECT_NO_THROW(stopConnection(test_connection));
}


TEST(ConnectionTest2, ClosedSocket) 
{
    http::server::connection test_connection(std::move(socket_));
    EXPECT_ANY_THROW(test_connection.do_read());
    EXPECT_ANY_THROW(test_connection.do_write());
}

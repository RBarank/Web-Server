#include "gtest/gtest.h"
#include "connection.hpp"
#include <boost/asio.hpp>



boost::asio::io_service io_service_;
boost::asio::ip::tcp::socket socket_(io_service_);
std::unordered_map<std::string, http::server::RequestHandler*> test_map;
std::unordered_map<std::string, std::string> nameMap;

void startConnection(http::server::connection& test_connection)
{
    test_connection.start();
}

void stopConnection(http::server::connection& test_connection)
{
    test_connection.stop();
}


TEST(ConnectionTest, constructor_tests) {
    http::server::connection test_connection(std::move(socket_), test_map, nameMap);
    EXPECT_FALSE(socket_.is_open());
    EXPECT_ANY_THROW(startConnection(test_connection));
    EXPECT_NO_THROW(stopConnection(test_connection));
}

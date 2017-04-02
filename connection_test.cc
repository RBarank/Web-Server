#include "gtest/gtest.h"
#include "connection.hpp"
#include <boost/asio.hpp>



boost::asio::io_service test_io_service;
boost::asio::ip::tcp::socket test_socket(test_io_service);
std::unordered_map<std::string, RequestHandler*> test_map;
std::unordered_map<std::string, std::string> name_map;

void StartConnection(Connection& test_connection)
{
    test_connection.Start();
}

void StopConnection(Connection& test_connection)
{
    test_connection.Stop();
}


TEST(ConnectionTest, Constructor_Tests) 
{
    Connection test_connection(std::move(test_socket), test_map, name_map);
    EXPECT_FALSE(test_socket.is_open());
    EXPECT_ANY_THROW(StartConnection(test_connection));
    EXPECT_NO_THROW(StopConnection(test_connection));
}

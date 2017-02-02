#include "gtest/gtest.h"
//#include "connection.hpp"
#include <boost/asio.hpp>


TEST(ServerTest, InvalidPortNumber) {
    EXPECT_EQ("aa", "aa");
}


g++ -std=c++0x -isystem googletest/googletest/include -pthread connection_test.cc -lboost_system googletest/googletest/src/gtest_main.cc libgtest.a -o connection_test

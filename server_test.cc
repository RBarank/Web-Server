#include "gtest/gtest.h"
#include "server.hpp"

int port_number = 3000;
http::server::server TEST_SERVER("127.0.0.1", std::to_string(port_number));


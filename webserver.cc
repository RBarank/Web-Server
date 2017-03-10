#include "config_parser.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "server.hpp"
#include <utility>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>
#include <thread>


http::server::server* s;

void checkChange(char* inputFile)
{
    std::time_t last = boost::filesystem::last_write_time(inputFile);
    while (last == boost::filesystem::last_write_time(inputFile)) {}
    s->kill();
}

void runServer(char* inputFile)
{
    NginxConfigParser config_parser;
    NginxConfig config;
    config_parser.Parse(inputFile, &config);
    
    std::thread t1(checkChange, inputFile);
    
    s = new http::server::server("0.0.0.0", config);
    s->run();
    t1.join();
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./webserver <path to config file>\n");
        return 1;
    }
    
    if ( !boost::filesystem::exists(argv[1]))
    {
        std::cout << "Can't find my file!" << std::endl;
        return 2;
    }
    
    while (true)
    {
        s = nullptr;
        runServer(argv[1]);
        delete s;
    }
    
    return 0;
    
}



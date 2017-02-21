#include "config_parser.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "server.hpp"
#include <utility>
#include <vector>
#include <iostream>


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./webserver <path to config file>\n");
        return 1;
    }
    
    NginxConfigParser config_parser;
    NginxConfig config;
    config_parser.Parse(argv[1], &config);
    /*    
    GetConfigInfo config_info = GetConfigInfo(config);
    int port_number = config_info.portNumber();
    if (port_number == -1)
    {
        std::cout << "Config file improperly formatted, port no is wrong." << std::endl;
        return 1;
    }

    std::cout << "port number " << port_number << std::endl;

    
    std::unordered_map<std::string, std::string> pathMapRoot = config_info.getPathMap(config);
    */
    try
    {
        http::server::server s("127.0.0.1", config);
        //s.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
    
}

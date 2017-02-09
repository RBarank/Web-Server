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
    
    std::string config_string = config.ToString().c_str();
    //std::cout << config_string << std::endl;
    
    GetConfigInfo port_stuff = GetConfigInfo(config);
    int port_number = port_stuff.portNumber();
    if (port_number == -1)
    {
        std::cout << "Config file improperly formatted" << std::endl;
        return 1;
    }
    
    std::cout << port_number << std::endl;
    std::unordered_map<std::string, std::string> pathMapRoot = port_stuff.getPathMap(config);
    
    std::unordered_map<std::string, std::string>::iterator it = pathMapRoot.begin();
    while (it != pathMapRoot.end()) {
        std::cout << it->first << " : " << it->second << "\n";
        it++;
    }

    /*    
    try
    {
        http::server::server s("127.0.0.1", std::to_string(port_number));
        s.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    */
    return 0;
    
}

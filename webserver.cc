#include "config_parser.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>


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
  std::cout << config_string << std::endl;


  std::unordered_map<std::string, std::string> args_map;
  
  int len = config_string.length();
  for (int i = 0; i < len; i++)
    {
      
    }
  
  





  /*
  size_t port_location = config_string.find("listen \D.*");
  if (port_location == -1)
    {
      printf("Listen not found in config string\n");
      exit(1);
    }
  port_location += 7; // the portno starts 7 chars after the l in listen
  string port_string = "";
  while (isdigit(config_string[port_location]))
    {
      
    }
  
  

  printf("The portno is %d\n", portno);




  return 0;
}

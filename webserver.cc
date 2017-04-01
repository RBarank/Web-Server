#include "config_parser.hpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "server.hpp"
#include <utility>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>
#include <thread>


Server* s;

void CheckChange(char* input_file)
{
  std::time_t last = boost::filesystem::last_write_time(input_file);
  while (last == boost::filesystem::last_write_time(input_file)) 
    {
    }
  s->Kill();
}

void RunServer(char* input_file)
{
  NginxConfigParser config_parser;
  NginxConfig config;
  config_parser.Parse(input_file, &config);
  
  std::thread t1(CheckChange, input_file);
  
  s = new Server("0.0.0.0", config);
  s->Run();
  t1.join();
}

int main(int argc, char* argv[])
{
  if (argc != 2)
    {
      printf("Usage: ./webserver <path to config file>\n");
      return 1;
    }
  
  if (!boost::filesystem::exists(argv[1]))
    {
      std::cout << "File not found!" << std::endl;
      return 2;
    }
  
  while (true)
    {
      s = nullptr;
      RunServer(argv[1]);
      delete s;
    }
  
  return 0;
  
}



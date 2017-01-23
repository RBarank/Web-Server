
all:
	g++ config_parser.cc webserver.cc -std=c++0x -g -Wall -o webserver  
clean:
	rm webserver

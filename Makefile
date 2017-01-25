all:
	g++ config_parser.cc webserver.cc -o webserver -std=c++0x -g -Wall -Werror -lboost_system -lpthread
	./webserver example_config
clean:
	rm webserver

all:
	g++ config_parser.cc reply.cc webserver.cc -std=c++0x -g -Wall -Werror -lboost_system -lpthread -o webserver
	./webserver example_config
clean:
	rm webserver

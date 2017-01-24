all:
	g++ config_parser.cc webserver.cc -std=c++0x -g -Wall -o webserver
	./webserver example_config
clean:
	rm webserver

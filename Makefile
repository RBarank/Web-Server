all:
	g++ config_parser.cc reply.cc webserver.cc -o webserver -std=c++0x -g -Wall -Werror -lboost_system -lpthread

run:
	g++ config_parser.cc reply.cc webserver.cc -o webserver -std=c++0x -g -Wall -Werror -lboost_system -lpthread
	./webserver config_file

clean:
	rm webserver

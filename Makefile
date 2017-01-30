all:
	g++ config_parser.cc connection.cc reply.cc webserver.cc -o webserver -std=c++0x -g -Wall -Werror -lboost_system -lpthread

run:
	g++ config_parser.cc connection.cc reply.cc webserver.cc -o webserver -std=c++0x -g -Wall -Werror -lboost_system -lpthread
	./webserver config_file

clean:
	rm webserver config_parser_test # plus rest of tests we add

test:
	./build_tests.sh # && ./run_all_tests??? or list them all one by one??

all:
	g++ config_parser.cc connection.cc webserver.cc server.cc -o webserver -std=c++0x -g -Wall -Werror -lboost_system -lpthread

run:
	g++ config_parser.cc connection.cc reply.cc webserver.cc -o webserver -std=c++0x -g -Wall -Werror -lboost_system -lpthread
	./webserver config_file

clean:
	rm webserver # plus rest of tests we add
emacs:
	rm *~
clean_tests:
	rm config_parser_test


test:
	./build_tests.sh # && ./run_all_tests??? or list them all one by one??

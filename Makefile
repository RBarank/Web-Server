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
	rm config_parser_test server_test connection_test

test:
	./build_tests.sh
	g++ -std=c++0x -isystem googletest/googletest/include -pthread server_test.cc server.cc connection.cc -lboost_system googletest/googletest/src/gtest_main.cc libgtest.a -o server_test
	g++ -std=c++0x -isystem googletest/googletest/include -pthread connection_test.cc connection.cc -lboost_system googletest/googletest/src/gtest_main.cc libgtest.a -o connection_test

integration:
	python integration.py


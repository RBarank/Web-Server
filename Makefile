all:
	g++ config_parser.cc connection.cc webserver.cc server.cc -o webserver -std=c++0x -g -Wall -Werror -lboost_system -lpthread

run:
	g++ config_parser.cc connection.cc reply.cc webserver.cc -o webserver -std=c++0x -g -Wall -Werror -lboost_system -lpthread
	./webserver config_file

clean:
	rm webserver

clean-emacs:
	rm *~

clean-tests:
	rm config_parser_test server_test connection_test

test:
	./build_tests.sh
	g++ -std=c++0x -isystem googletest/googletest/include -pthread server_test.cc server.cc connection.cc -lboost_system googletest/googletest/src/gtest_main.cc libgtest.a -o server_test -fprofile-arcs -ftest-coverage
	g++ -std=c++0x -isystem googletest/googletest/include -pthread connection_test.cc connection.cc -lboost_system googletest/googletest/src/gtest_main.cc libgtest.a -o connection_test -fprofile-arcs -ftest-coverage
	./server_test && ./connection_test && ./config_parser_test

integration:
	python integration.py

coverage: test
	gcov -r server.cc connection.cc config_parser.cc

clean_coverage:
	rm *gcov *gcda *gcno

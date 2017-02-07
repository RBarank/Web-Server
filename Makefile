GTEST_DIR = googletest/googletest
STD_FLAGS = -std=c++0x -g -Wall -Werror -pthread -lboost_system
COV_FLAGS = -isystem $(GTEST_DIR)/include -fprofile-arcs -ftest-coverage libgtest.a $(GTEST_DIR)/src/gtest_main.cc

all:
	g++ config_parser.cc connection.cc server.cc reply.cc webserver.cc -o webserver $(STD_FLAGS)

run:
	g++ config_parser.cc connection.cc server.cc reply.cc webserver.cc -o webserver $(STD_FLAGS)
	./webserver config_file

clean:
	rm webserver

clean-emacs:
	rm *~

clean-tests:
	rm config_parser_test server_test connection_test

test:
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
	g++ config_parser_test.cc config_parser.cc -o config_parser_test $(STD_FLAGS) $(COV_FLAGS)
	g++ server_test.cc server.cc connection.cc reply.cc -o server_test $(STD_FLAGS) $(COV_FLAGS)
	g++ connection_test.cc connection.cc reply.cc -o connection_test $(STD_FLAGS) $(COV_FLAGS)
	./server_test && ./connection_test && ./config_parser_test

integration:
	python integration.py

coverage: test
	gcov -r server.cc connection.cc config_parser.cc

clean-coverage:
	rm *gcov *gcda *gcno

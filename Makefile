GTEST_DIR = googletest/googletest
STD_FLAGS = -std=c++11 -g -Wall -Werror -pthread -lboost_system
COV_FLAGS = -isystem $(GTEST_DIR)/include -fprofile-arcs -ftest-coverage libgtest.a $(GTEST_DIR)/src/gtest_main.cc

all:
	g++ config_parser.cc connection.cc server.cc reply.cc webserver.cc mime-types.cc request_handler.cc echo_handler.cc static_handler.cc -o webserver $(STD_FLAGS)

run:
	g++ config_parser.cc connection.cc server.cc reply.cc webserver.cc mime-types.cc request_handler.cc echo_handler.cc static_handler.cc -o webserver $(STD_FLAGS)
	./webserver config_file

clean:
	rm webserver

clean-emacs:
	rm *~

clean-tests:
	rm -f config_parser_test server_test connection_test reply_test request_handler_test echo_handler_test static_handler_test

test:
	g++ -std=c++11 -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
	g++ config_parser_test.cc config_parser.cc -o config_parser_test $(STD_FLAGS) $(COV_FLAGS)
	g++ server_test.cc server.cc connection.cc reply.cc mime-types.cc request_handler.cc echo_handler.cc static_handler.cc -o server_test $(STD_FLAGS) $(COV_FLAGS)
	g++ connection_test.cc connection.cc reply.cc mime-types.cc request_handler.cc echo_handler.cc static_handler.cc -o connection_test $(STD_FLAGS) $(COV_FLAGS)
	g++ reply.cc reply_test.cc -o reply_test $(STD_FLAGS) $(COV_FLAGS)
	./server_test && ./connection_test && ./config_parser_test &&./reply_test

integration:
	python integration.py

coverage: test
	gcov -r server.cc connection.cc config_parser.cc reply.cc

clean-coverage:
	rm *gcov *gcda *gcno

handler_test:
	g++ -std=c++11 -isystem ${GTEST_DIR}/include -pthread request_handler_test.cc request_handler.cc echo_handler.cc static_handler.cc reply.cc mime-types.cc ${GTEST_DIR}/src/gtest_main.cc libgtest.a -o request_handler_test -lboost_system
	./request_handler_test
	g++ -std=c++11 -isystem ${GTEST_DIR}/include -pthread echo_handler_test.cc echo_handler.cc reply.cc ${GTEST_DIR}/src/gtest_main.cc libgtest.a -o echo_handler_test -lboost_system
	./echo_handler_test
	g++ -std=c++11 -isystem ${GTEST_DIR}/include -pthread static_handler_test.cc static_handler.cc reply.cc mime-types.cc ${GTEST_DIR}/src/gtest_main.cc libgtest.a -o static_handler_test -lboost_system
	./static_handler_test

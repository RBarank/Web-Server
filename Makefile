GTEST_DIR = googletest/googletest
STD_FLAGS = -std=c++11 -g -Wall -Werror -pthread -lboost_system
COV_FLAGS = -isystem $(GTEST_DIR)/include -fprofile-arcs -ftest-coverage libgtest.a $(GTEST_DIR)/src/gtest_main.cc

all:
	g++ config_parser.cc connection.cc server.cc response.cc request.cc webserver.cc mime-types.cc request_handler.cc echo_handler.cc static_handler.cc not_found_handler.cc server_info.cc status_handler.cc -o webserver $(STD_FLAGS) -pthread

run:	all
	./webserver config_file

clean:
	rm webserver

clean-emacs:
	rm *~

clean-tests:
	rm -f config_parser_test server_test connection_test response_test request_handler_test echo_handler_test static_handler_test request_test response_test

test:
	g++ -std=c++11 -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
	g++ server_test.cc server.cc server_info.cc config_parser.cc connection.cc response.cc request.cc mime-types.cc request_handler.cc echo_handler.cc static_handler.cc -o server_test $(STD_FLAGS) $(COV_FLAGS)
	g++ connection_test.cc connection.cc server_info.cc response.cc request.cc mime-types.cc request_handler.cc echo_handler.cc static_handler.cc -o connection_test $(STD_FLAGS) $(COV_FLAGS)
	g++ response.cc request.cc response_test.cc -o response_test $(STD_FLAGS) $(COV_FLAGS)
	g++ response.cc request.cc request_test.cc -o request_test $(STD_FLAGS) $(COV_FLAGS)
	g++ config_parser_test.cc config_parser.cc -o config_parser_test $(STD_FLAGS) $(COV_FLAGS)
	./server_test && ./connection_test && ./config_parser_test &&./response_test && ./request_test

integration:
	python integration.py

coverage: test
	gcov -r server.cc connection.cc config_parser.cc response.cc request.cc request_handler.cc

clean-coverage:
	rm -rf *gcov *gcda *gcno *.dSYM

handler_test:
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -pthread server_info_test.cc server_info.cc response.cc ${GTEST_DIR}/src/gtest_main.cc libgtest.a -o server_info_test -lboost_system -fprofile-arcs -ftest-coverage
	./server_info_test
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -pthread status_handler.cc status_handler_test.cc request_handler.cc request.cc response.cc ${GTEST_DIR}/src/gtest_main.cc server_info.cc libgtest.a -o status_handler_test -lboost_system -fprofile-arcs -ftest-coverage
	./status_handler_test
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -pthread not_found_handler.cc not_found_handler_test.cc request_handler.cc request.cc response.cc ${GTEST_DIR}/src/gtest_main.cc server_info.cc libgtest.a -o not_found_handler_test -lboost_system -fprofile-arcs -ftest-coverage
	./not_found_handler_test
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -pthread echo_handler.cc echo_handler_test.cc request_handler.cc request.cc response.cc ${GTEST_DIR}/src/gtest_main.cc server_info.cc libgtest.a -o echo_handler_test -lboost_system -fprofile-arcs -ftest-coverage
	./echo_handler_test
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -pthread static_handler.cc static_handler_test.cc config_parser.cc request_handler.cc request.cc response.cc ${GTEST_DIR}/src/gtest_main.cc server_info.cc mime-types.cc libgtest.a -o static_handler_test -lboost_system -fprofile-arcs -ftest-coverage
	./static_handler_test
	g++ request_handler_test.cc request_handler.cc static_handler.cc response.cc request.cc mime-types.cc -o request_handler_test $(STD_FLAGS) $(COV_FLAGS)
	./request_handler_test


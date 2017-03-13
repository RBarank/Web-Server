GTEST_DIR = googletest/googletest

CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Werror
LDFLAGS = -static-libgcc -static-libstdc++ -pthread -Wl,-Bstatic -lboost_system -lboost_regex -lboost_iostreams -lz -lboost_filesystem
TEST_FLAGS = -fprofile-arcs -ftest-coverage libgtest.a -isystem $(GTEST_DIR)/include $(GTEST_DIR)/src/gtest_main.cc
SRC = config_parser.cc connection.cc server.cc response.cc request.cc webserver.cc \
	mime-types.cc request_handler.cc echo_handler.cc static_handler.cc  \
	not_found_handler.cc server_info.cc status_handler.cc proxy_handler.cc \
	cpp-markdown/markdown.cpp cpp-markdown/markdown-tokens.cpp

# TODO:
# create variables representing dependencies for each cc file and those when compiling cc files for tests
# create separate LDFLAGS for each cc file and use those LDFLAGS compiling cc files for tests
# split make test into a separate target for each test file that builds and runs a test for one cc file


.PHONY: all run test clean clean-tests clean-coverage clean-all deploy push_deploy


all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o webserver

run: all
	./webserver config_file

push_deploy: 
	docker save httpserver | bzip2 | ssh -i Razzle-Dazzlepair.pem ubuntu@ec2-35-161-79-255.us-west-2.compute.amazonaws.com 'bunzip2 | docker load && docker stop $$(docker ps -a -q) && docker run --rm -t -p 8080:8080 httpserver'

deploy:
	rm -rf deploy
	mkdir deploy
	docker build -t httpserver.build .
	docker run --rm httpserver.build > binary.tar
	tar -xvf binary.tar -C ./deploy
	cp Dockerfile.run deploy/
	cp deploy_config deploy/
	cp -r test_folder deploy/
	cp index.html deploy/
	docker build -t httpserver -f deploy/Dockerfile.run ./deploy

	rm -f binary.tar

clean:
	rm -f webserver

clean-tests:
	for x in *_test; do rm -f $$x; done

clean-coverage:
	rm -f *gcov *gcda *gcno *.dSYM

clean-all: clean clean-tests clean-coverage

test:
	g++ -std=c++11 -pthread -c -isystem ${GTEST_DIR}/include -I${GTEST_DIR} ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

	$(CXX) server_test.cc server.cc server_info.cc config_parser.cc connection.cc response.cc request.cc mime-types.cc request_handler.cc echo_handler.cc static_handler.cc cpp-markdown/markdown.cpp cpp-markdown/markdown-tokens.cpp -o server_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) connection_test.cc connection.cc server_info.cc response.cc request.cc mime-types.cc request_handler.cc echo_handler.cc static_handler.cc cpp-markdown/markdown.cpp cpp-markdown/markdown-tokens.cpp -o connection_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) response.cc request.cc response_test.cc -o response_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) response.cc request.cc request_test.cc -o request_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) config_parser_test.cc config_parser.cc -o config_parser_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) server_info_test.cc server_info.cc response.cc -o server_info_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) status_handler.cc status_handler_test.cc request_handler.cc request.cc response.cc server_info.cc -o status_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) not_found_handler.cc not_found_handler_test.cc request_handler.cc request.cc response.cc -o not_found_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) echo_handler.cc echo_handler_test.cc request_handler.cc request.cc response.cc server_info.cc -o echo_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) static_handler.cc static_handler_test.cc config_parser.cc request_handler.cc request.cc response.cc server_info.cc mime-types.cc cpp-markdown/markdown.cpp cpp-markdown/markdown-tokens.cpp -o static_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) request_handler_test.cc request_handler.cc static_handler.cc response.cc request.cc mime-types.cc cpp-markdown/markdown.cpp cpp-markdown/markdown-tokens.cpp -o request_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)
	$(CXX) proxy_handler_test.cc proxy_handler.cc request_handler.cc response.cc request.cc config_parser.cc server_info.cc -o proxy_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

        # Run all the tests:
	for x in *_test; do ./$$x; done

integration: all
	python integration.py

coverage: test
	gcov -r $(filter-out webserver.cc, $(SRC))

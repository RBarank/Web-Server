GTEST_DIR = googletest/googletest
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = test

CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Werror
LDFLAGS = -static-libgcc -static-libstdc++ -pthread -Wl,-Bstatic -lboost_system -lboost_regex -lboost_iostreams -lz -lboost_filesystem
TEST_FLAGS = -fprofile-arcs -ftest-coverage libgtest.a -isystem $(GTEST_DIR)/include $(GTEST_DIR)/src/gtest_main.cc

SRC_FILES = $(SRC_DIR)/*.cc $(SRC_DIR)/cpp-markdown/*.cpp

#config_parser.cc connection.cc server.cc response.cc request.cc webserver.cc \
#	mime-types.cc request_handler.cc echo_handler.cc static_handler.cc  \
#	not_found_handler.cc server_info.cc status_handler.cc proxy_handler.cc \
#	cpp-markdown/markdown.cpp cpp-markdown/markdown-tokens.cpp

# TODO:
# create variables representing dependencies for each cc file and those when compiling cc files for tests
# create separate LDFLAGS for each cc file and use those LDFLAGS compiling cc files for tests
# split make test into a separate target for each test file that builds and runs a test for one cc file


.PHONY: all run test clean clean-tests clean-coverage clean-all deploy push_deploy


all:
	$(CXX) $(SRC_FILES) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/webserver

run: all
	./$(BIN_DIR)/webserver config_file

push_deploy: 
	docker save httpserver | bzip2 | ssh -i Razzle-Dazzlepair.pem ubuntu@ec2-35-161-79-255.us-west-2.compute.amazonaws.com 'bunzip2 | docker load && docker stop $$(docker ps -a -q) && docker run --rm -t -p 8020:8020 httpserver'

deploy:
	rm -rf deploy
	mkdir deploy
	docker build -t httpserver.build .
	docker run --rm httpserver.build > binary.tar
	tar -xvf binary.tar -C ./deploy
	cp Dockerfile.run deploy/
	cp deploy_config deploy/
	cp -r static deploy/
	docker build -t httpserver -f deploy/Dockerfile.run ./deploy
	rm -f binary.tar

clean:
	rm -f $(BIN_DIR)/webserver $(BIN_DIR)/compressionTest.txt

clean-tests:
	for x in $(BIN_DIR)/*_test; do rm -f $$x; done

clean-coverage:
	rm -f $(BIN_DIR)/*gcov $(BIN_DIR)/*gcda $(BIN_DIR)/*gcno $(BIN_DIR)/*.dSYM

clean-all: clean clean-tests clean-coverage


test:
	g++ -std=c++11 -pthread -c -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

	$(CXX) $(TEST_DIR)/server_test.cc $(SRC_DIR)/server.cc $(SRC_DIR)/server_info.cc $(SRC_DIR)/config_parser.cc $(SRC_DIR)/connection.cc $(SRC_DIR)/response.cc $(SRC_DIR)/request.cc $(SRC_DIR)/mime-types.cc $(SRC_DIR)/request_handler.cc $(SRC_DIR)/echo_handler.cc $(SRC_DIR)/static_handler.cc $(SRC_DIR)/cpp-markdown/markdown.cpp $(SRC_DIR)/cpp-markdown/markdown-tokens.cpp -o $(BIN_DIR)/server_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(TEST_DIR)/connection_test.cc $(SRC_DIR)/connection.cc $(SRC_DIR)/server_info.cc $(SRC_DIR)/response.cc $(SRC_DIR)/request.cc $(SRC_DIR)/mime-types.cc $(SRC_DIR)/request_handler.cc $(SRC_DIR)/echo_handler.cc $(SRC_DIR)/static_handler.cc $(SRC_DIR)/cpp-markdown/markdown.cpp $(SRC_DIR)/cpp-markdown/markdown-tokens.cpp -o $(BIN_DIR)/connection_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(SRC_DIR)/response.cc $(SRC_DIR)/request.cc $(TEST_DIR)/response_test.cc -o $(BIN_DIR)/response_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(SRC_DIR)/response.cc $(SRC_DIR)/request.cc $(TEST_DIR)/request_test.cc -o $(BIN_DIR)/request_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(TEST_DIR)/config_parser_test.cc $(SRC_DIR)/config_parser.cc -o $(BIN_DIR)/config_parser_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(TEST_DIR)/server_info_test.cc $(SRC_DIR)/server_info.cc $(SRC_DIR)/response.cc -o $(BIN_DIR)/server_info_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(SRC_DIR)/status_handler.cc $(TEST_DIR)/status_handler_test.cc $(SRC_DIR)/request_handler.cc $(SRC_DIR)/request.cc $(SRC_DIR)/response.cc $(SRC_DIR)/server_info.cc -o $(BIN_DIR)/status_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(SRC_DIR)/not_found_handler.cc $(TEST_DIR)/not_found_handler_test.cc $(SRC_DIR)/request_handler.cc $(SRC_DIR)/request.cc $(SRC_DIR)/response.cc -o $(BIN_DIR)/not_found_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(SRC_DIR)/echo_handler.cc $(TEST_DIR)/echo_handler_test.cc $(SRC_DIR)/request_handler.cc $(SRC_DIR)/request.cc $(SRC_DIR)/response.cc $(SRC_DIR)/server_info.cc -o $(BIN_DIR)/echo_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(SRC_DIR)/static_handler.cc $(TEST_DIR)/static_handler_test.cc $(SRC_DIR)/config_parser.cc $(SRC_DIR)/request_handler.cc $(SRC_DIR)/request.cc $(SRC_DIR)/response.cc $(SRC_DIR)/server_info.cc $(SRC_DIR)/mime-types.cc $(SRC_DIR)/cpp-markdown/markdown.cpp $(SRC_DIR)/cpp-markdown/markdown-tokens.cpp -o $(BIN_DIR)/static_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(TEST_DIR)/request_handler_test.cc $(SRC_DIR)/request_handler.cc $(SRC_DIR)/static_handler.cc $(SRC_DIR)/response.cc $(SRC_DIR)/request.cc $(SRC_DIR)/mime-types.cc $(SRC_DIR)/cpp-markdown/markdown.cpp $(SRC_DIR)/cpp-markdown/markdown-tokens.cpp -o $(BIN_DIR)/request_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

	$(CXX) $(TEST_DIR)/proxy_handler_test.cc $(SRC_DIR)/proxy_handler.cc $(SRC_DIR)/request_handler.cc $(SRC_DIR)/response.cc $(SRC_DIR)/request.cc $(SRC_DIR)/config_parser.cc $(SRC_DIR)/server_info.cc -o $(BIN_DIR)/proxy_handler_test $(CXXFLAGS) $(LDFLAGS) $(TEST_FLAGS)

        # Run all the tests:
	for x in *_test; do ./$$x; done

integration: all
	python $(TEST_DIR)/integration.py

coverage: test
	gcov -r $(filter-out webserver.cc, $(SRC))

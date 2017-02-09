#include "gtest/gtest.h"
#include "config_parser.h"
#include <string>



TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("config_file", &out_config);

  EXPECT_TRUE(success);
}

TEST(NginxConfigStatementTest, toString) {
	NginxConfigStatement st;
	EXPECT_EQ(st.ToString(0), ";\n");
}

TEST(NginxConfigStatementTest2, toString2) {
	NginxConfigStatement st;
	EXPECT_EQ(st.ToString(-1), ";\n");
	st.tokens_.push_back("foo");
	st.tokens_.push_back("bar");
	EXPECT_EQ(st.ToString(0), "foo bar;\n");
}

class NginxStringConfigTest : public ::testing::Test {
protected:
	bool ParseString(const std::string config_string) {
		std::stringstream config_stream(config_string);
		return parser_.Parse(&config_stream, &out_config_);
	}
	NginxConfigParser parser_;
	NginxConfig out_config_;
};

TEST_F(NginxStringConfigTest, AnotherSimpleConfig) {
	EXPECT_TRUE(ParseString("foo bar;"));
	EXPECT_EQ(1, out_config_.statements_.size())
		<< "Config has one statements";
	EXPECT_EQ("foo", out_config_.statements_.at(0)->tokens_.at(0));
}

TEST_F(NginxStringConfigTest, InvalidConfig) {
	EXPECT_FALSE(ParseString("foo bar"));
}

TEST_F(NginxStringConfigTest, NestedConfig) {
	EXPECT_TRUE(ParseString("server { listen 80; }"));
}

TEST_F(NginxStringConfigTest, UnbalancedCurlyBraces) {
	EXPECT_FALSE(ParseString("server { port 3000; "));
}

TEST(GetPortNumberTest, check_different_ports) {
    for (int i = 1; i <= 5; i++)
    {
        NginxConfigParser parser;
        NginxConfig out_config;
        std::string tmp = "test_file/config_file"+std::to_string(i);
        parser.Parse(tmp.c_str(), &out_config);
        GetConfigInfo confif_info = GetConfigInfo(out_config);
        EXPECT_EQ(confif_info.portNumber(), -1);
        std::unordered_map<std::string, std::string> mapper = confif_info.getPathMap(out_config);
    }
    
    NginxConfigParser parser;
    NginxConfig out_config;
    std::string tmp = "config_file";
    parser.Parse(tmp.c_str(), &out_config);
    GetConfigInfo port_stuff = GetConfigInfo(out_config);
    EXPECT_EQ(port_stuff.portNumber(), 3000);
}

TEST(PathTest, path_static_echo) {
    NginxConfigParser parser;
    NginxConfig out_config;
    std::string tmp = "test_file/config_file6";
    parser.Parse(tmp.c_str(), &out_config);
    GetConfigInfo config_info = GetConfigInfo(out_config);
    std::unordered_map<std::string, std::string> pathMapRoot = config_info.getPathMap(out_config);
    EXPECT_EQ(pathMapRoot["/echo"], "");
    EXPECT_EQ(pathMapRoot["/static"], "/test_folder");
}


TEST(PathTest, path_static_echo2) {
    NginxConfigParser parser;
    NginxConfig out_config;
    std::string tmp = "test_file/config_file7";
    parser.Parse(tmp.c_str(), &out_config);
    GetConfigInfo config_info = GetConfigInfo(out_config);
    std::unordered_map<std::string, std::string> pathMapRoot = config_info.getPathMap(out_config);
    EXPECT_EQ(pathMapRoot["/echo"], "");
    EXPECT_EQ(pathMapRoot["/static"], "");
}


TEST(PathTest, path_static_echo3) {
    NginxConfigParser parser;
    NginxConfig out_config;
    std::string tmp = "test_file/config_file8";
    parser.Parse(tmp.c_str(), &out_config);
    GetConfigInfo config_info = GetConfigInfo(out_config);
    std::unordered_map<std::string, std::string> pathMapRoot = config_info.getPathMap(out_config);
    EXPECT_EQ(pathMapRoot["/echo"], "");
    EXPECT_EQ(pathMapRoot["/static"], "/test_folder");
    EXPECT_EQ(pathMapRoot["/static2"], "/testing_folder");
    EXPECT_EQ(pathMapRoot["/static3"], "/test");
}





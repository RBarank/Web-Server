#include "echo_handler.hpp"
#include "static_handler.hpp"

namespace http {
	namespace server {

		const std::string ECHO_URL = "/echo";
		const std::string STATIC_URL = "/static";
		request_handler* request_handler::generateHandler(std::string& url, std::string& root){
			if(url == ECHO_URL)
				return new echo_handler();
			else if(url == STATIC_URL && !root.empty())
				return new static_handler(root);
			else
				return NULL;
		}
	}
}

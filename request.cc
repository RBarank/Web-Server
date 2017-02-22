#include "request.hpp"

namespace http{
	namespace server{
		static unique_ptr<Request> Request::Parse(const std::string& raw_request){
			//std::cout << "request begin\n" << request_.content << "response end" << std::endl;
			unique_ptr<Request> req = std::make_unique<Request>();
			req.rawRequest = raw_request;
			// use boost tokenizer to parse request
		  	//const std::string req_str(request_.content);
		  	boost::char_separator<char> separator{" "};
		  	boost::tokenizer<boost::char_separator<char>> tokens(req_str, separator);
		  	boost::tokenizer<boost::char_separator<char>>::iterator tokens_it = tokens.begin();

		  	//request_.method = *(tokens_it);
		  	req.method = *(tokens_it);
		  	++tokens_it;
		  	req.uri = *(tokens_it);
		  	++tokens_it
		  	req.version = *(tokens_it);

		  	return req;
		  	//std::cout << "request_method: " << request_.method << "\nrequest_uri: " << request_.uri << std::endl;
		  	// size_t secondSlash = request_.uri.substr(1).find_first_of("/");
		  	// request_.base = request_.uri.substr(0,secondSlash + 1);
		  	// std::cout << "request_base: " << request_.base << std::endl;
		}

      	std::string Request::raw_request() const{
      		return rawRequest;
      	}
      	std::string Request::method() const{
      		return method;
      	}
      	std::string Request::uri() const{
      		return uri;
      	}
      	std::string Request::version() const{
      		return version;
      	}

      	// using Headers = std::vector<std::pair<std::string, std::string>>;
      	// Headers Request::headers() const;

      	//std::string Request::body() const;
	}
}
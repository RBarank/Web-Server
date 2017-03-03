#include "request.hpp"
#include <boost/tokenizer.hpp>

namespace http{
  namespace server{
    std::unique_ptr<Request> Request::Parse(const std::string& raw_request){
      //std::cout << "request begin\n" << request_.content << "response end" << std::endl;
      std::unique_ptr<Request> req(new Request);
      req->raw_request_ = raw_request;
      // use boost tokenizer to parse request
      //const std::string req_str(request_.content);

      boost::char_separator<char> separator{"\r\n\r\n"};
      boost::tokenizer<boost::char_separator<char>> tokens(req->raw_request_, separator);
      boost::tokenizer<boost::char_separator<char>>::iterator tokens_it = tokens.begin();
      
      boost::char_separator<char> separator1{"\r\n"};
      boost::tokenizer<boost::char_separator<char>> tokens1(*(tokens_it), separator1);
      boost::tokenizer<boost::char_separator<char>>::iterator tokens_it1 = tokens1.begin();

      ++tokens_it;
      req->body_ = *(tokens_it);

      boost::char_separator<char> separator2{" "};
      boost::tokenizer<boost::char_separator<char>> tokens2(*(tokens_it1), separator2);
      boost::tokenizer<boost::char_separator<char>>::iterator tokens_it2 = tokens2.begin();
      
      //request_.method = *(tokens_it);
      req->method_ = *(tokens_it2);
      ++tokens_it2;
      req->uri_ = *(tokens_it2);
      ++tokens_it2;
      req->version_ = *(tokens_it2);

      ++tokens_it1;
      for ( ; tokens_it1 != tokens.end(); ++tokens_it1){
        boost::char_separator<char> sep{": "};
        boost::tokenizer<boost::char_separator<char>> tokens3(*(tokens_it1), sep);
        tokens_it2 = tokens3.begin();
        std::string header_name = *(tokens_it2);
        ++tokens_it2;
        std::string header_value = *(tokens_it2);
        req->headers_.push_back(std::make_pair(header_name, header_value));
      }
      return req;
      //std::cout << "request_method: " << request_.method << "\nrequest_uri: " << request_.uri << std::endl;
      // size_t secondSlash = request_.uri.substr(1).find_first_of("/");
      // request_.base = request_.uri.substr(0,secondSlash + 1);
      // std::cout << "request_base: " << request_.base << std::endl;
    }
    
    std::string Request::raw_request() const{
      return raw_request_;
    }
    std::string Request::method() const{
      return method_;
    }
    std::string Request::uri() const{
      return uri_;
    }
    std::string Request::version() const{
      return version_;
    }
    
    using Headers = std::vector<std::pair<std::string, std::string>>;
    Headers Request::headers() const {
      return headers_;
    }
    
    std::string Request::body() const {
      return body_;
    }


	void Request::set_raw_request(std::string raw_request)
	{
		raw_request_ = raw_request;
	}
	void Request::set_method(std::string method)
	{
		method_ = method;
	}
	void Request::set_uri(std::string uri)
	{
		uri_= uri;
	}
	void Request::set_version(std::string version)
	{
		version_ = version;
	}
	void Request::set_body(std::string body)
	{
		body_ = body;
	}
	void Request::set_headers(Headers headers)
	{
		headers_ = headers;
	}
  }
}

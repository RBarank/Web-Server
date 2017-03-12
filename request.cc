#include "request.hpp"
#include <boost/tokenizer.hpp>
#include <sstream>
#include <iostream>

namespace http{
  namespace server{
    std::unique_ptr<Request> Request::Parse(const std::string& raw_request){
      
      std::unique_ptr<Request> req(new Request);
      req->raw_request_ = raw_request;
            
      size_t split_by_line = raw_request.find("\r\n");
      std::string request_line  = raw_request.substr(0, split_by_line);
      
      size_t method_end = request_line.find(" ");
      req->method_ = request_line.substr(0, method_end);

      size_t uri_end = request_line.find(" ", method_end+1);
      req->uri_ = request_line.substr(method_end+1, uri_end-method_end-1);

      req->version_ = request_line.substr(uri_end+1);

      size_t end_of_headers = raw_request.find("\r\n\r\n");

      size_t end_of_last_line;
      size_t separator9;
      std::string cur_header;
      std::string header_name;
      std::string header_value;
      while (split_by_line < end_of_headers)
	{
	  end_of_last_line = split_by_line;
	  split_by_line = raw_request.find("\r\n", split_by_line+2);
	  cur_header = raw_request.substr(end_of_last_line+2, split_by_line - end_of_last_line - 2);
	  separator9 = cur_header.find(": ");
	  header_name = cur_header.substr(0, separator9);
	  header_value = cur_header.substr(separator9+2);
	  req->headers_.push_back(std::make_pair(header_name, header_value));
	}
      
      req->body_ = raw_request.substr(split_by_line+4);
      
      /*
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
	std::cout << std::endl << "IN PARSE REQUEST HEADER FIND" << std::endl; 
        boost::char_separator<char> sep{": "};
        boost::tokenizer<boost::char_separator<char>> tokens3(*(tokens_it1), sep);
        tokens_it2 = tokens3.begin();
        std::string header_name = *(tokens_it2);
        ++tokens_it2;
        std::string header_value = *(tokens_it2);
        req->headers_.push_back(std::make_pair(header_name, header_value));
      }
      */
      
      std::cout << "------------------NEW------------------------" << std::endl;
      std::cout << "METHOD " << req->method().size() << " "<< req->method() << std::endl;
      std::cout << "URI " << req->uri().size() << " "<< req->uri() << std::endl;
      std::cout << "VERSION " << req->version().size() << " "<< req->version() << std::endl;
      std::cout << "BODY " << req->body().size() << " "<< req->body() << std::endl;
      for (const auto& it : req->headers())
	{
	  std::cout << "HEADER: " << it.first << " " << it.second << std::endl;
	}

      std::cout << "------------------NEW------------------------" << std::endl;

      return req;
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

    std::string Request::get_header(const std::string header_name)
    {
      std::cout << "get_header HEADERS SIZE: " << headers_.size() << std::endl;
      for (size_t i = 0; i < headers_.size(); i++)
	{
	  std::cout << std::endl << "get_header HEADER: " << headers_[i].first << std::endl;
	  if (headers_[i].first == header_name)
	    {
	      return headers_[i].second;
	    }
	}
      return "";
    }
    
  }
}

#include "response.hpp"

namespace http{
  namespace server{
    namespace status_strings {
      
      const std::string ok =
	"HTTP/1.1 200 OK";
      const std::string created =
	"HTTP/1.1 201 Created";
      const std::string accepted =
	"HTTP/1.1 202 Accepted";
      const std::string no_content =
	"HTTP/1.1 204 No Content";
      const std::string multiple_choices =
	"HTTP/1.1 300 Multiple Choices";
      const std::string moved_permanently =
	"HTTP/1.1 301 Moved Permanently";
      const std::string moved_temporarily =
	"HTTP/1.1 302 Moved Temporarily";
      const std::string not_modified =
	"HTTP/1.1 304 Not Modified";
      const std::string bad_request =
	"HTTP/1.1 400 Bad Request";
      const std::string unauthorized =
	"HTTP/1.1 401 Unauthorized";
      const std::string forbidden =
	"HTTP/1.1 403 Forbidden";
      const std::string not_found =
	"HTTP/1.1 404 Not Found";
      const std::string internal_server_error =
	"HTTP/1.1 500 Internal Server Error";
      const std::string not_implemented =
	"HTTP/1.1 501 Not Implemented";
      const std::string bad_gateway =
	"HTTP/1.1 502 Bad Gateway";
      const std::string service_unavailable =
	"HTTP/1.1 503 Service Unavailable";
      
      std::string response_code_to_string(Response::ResponseCode status)
      {
	switch (status)
	  {
	  case Response::ok:
	    return ok;
	  case Response::created:
	    return created;
	  case Response::accepted:
	    return accepted;
	  case Response::no_content:
	    return no_content;
	  case Response::multiple_choices:
	    return multiple_choices;
	  case Response::moved_permanently:
	    return moved_permanently;
	  case Response::moved_temporarily:
	    return moved_temporarily;
	  case Response::not_modified:
	    return not_modified;
	  case Response::bad_request:
	    return bad_request;
	  case Response::unauthorized:
	    return unauthorized;
	  case Response::forbidden:
	    return forbidden;
	  case Response::not_found:
	    return not_found;
	  case Response::internal_server_error:
	    return internal_server_error;
	  case Response::not_implemented:
	    return not_implemented;
	  case Response::bad_gateway:
	    return bad_gateway;
	  case Response::service_unavailable:
	    return service_unavailable;
	  default:
	    return internal_server_error;
	  }
      }
      
    } // namespace status_strings
    
    void Response::SetStatus(const ResponseCode response_code){
      response_code_ = response_code;
    }

    void Response::AddHeader(const std::string& header_name, const std::string& header_value)
    {
      headers_.push_back(std::make_pair(header_name, header_value));
    }

    bool Response::SetHeader(const std::string header_name, const std::string header_value)
    {
      for (auto& header : headers_)
	{
	  if (header.first == header_name)
	    {
	      header.second = header_value;
	      std::cout << "header first,second: " << header.first << "," << header.second << std::endl;
	      return true;
	    }
	}
      return false;
    }

    void Response::SetBody(const std::string& body){
      body_ = body;
    }
    
    std::string Response::ToString(){
      const std::string CRLF = "\r\n";
      std::string response_str = status_strings::response_code_to_string(response_code_) + CRLF;
      for (auto header : headers_)
	{
	  response_str += header.first + ": " + header.second + CRLF;
	}
      response_str += CRLF; // there is an extra CRLF between last header and body of response
      response_str += body_;
      return response_str;
    }
    
    Response Response::stock_response(Response::ResponseCode status)
    {
      Response resp;
      resp.response_code_ = status;
      resp.body_ = status_strings::response_code_to_string(status);
      resp.headers_.push_back(std::make_pair("Content-Length", std::to_string(resp.body_.size())));
      resp.headers_.push_back(std::make_pair("Content-Type", "text/html"));            
      return resp;
    }
  }
}

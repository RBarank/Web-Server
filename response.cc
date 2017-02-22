#include "response.h"

namespace http{
  namespace server{
    namespace status_strings {
      
      const std::string ok =
	"200 OK";
      const std::string created =
	"201 Created";
      const std::string accepted =
	"202 Accepted";
      const std::string no_content =
	"204 No Content";
      const std::string multiple_choices =
	"300 Multiple Choices";
      const std::string moved_permanently =
	"301 Moved Permanently";
      const std::string moved_temporarily =
	"302 Moved Temporarily";
      const std::string not_modified =
	"304 Not Modified";
      const std::string bad_request =
	"400 Bad Request";
      const std::string unauthorized =
	"401 Unauthorized";
      const std::string forbidden =
	"403 Forbidden";
      const std::string not_found =
	"404 Not Found";
      const std::string internal_server_error =
	"500 Internal Server Error";
      const std::string not_implemented =
	"501 Not Implemented";
      const std::string bad_gateway =
	"502 Bad Gateway";
      const std::string service_unavailable =
	"503 Service Unavailable";
      
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
    void Response::AddHeader(const std::string& header_name, const std::string& header_value){
      headers_.push_back(std:make_pair<header_name, header_value>);
    }
    void Response::SetBody(const std::string& body){
      body_ = body;
    }
    
    std::string Response::ToString(){
      const std::string CRLF = "\r\n";
      std::string response_str = version_ + " " + response_code_to_string(response_code_) + CRLF;
      for (auto header : headers_)
	{
	  response_str += header.first + ": " + header.second + CRLF;
	}
      response_str += CRLF; // there is an extra CRLF between last header and body of response
      response_str += body_;
      return outputResponse;
    }
        
    namespace stock_replies {
      
      const char ok[] = "";
      const char created[] =
	"<html>"
	"<head><title>Created</title></head>"
	"<body><h1>201 Created</h1></body>"
	"</html>";
      const char accepted[] =
	"<html>"
	"<head><title>Accepted</title></head>"
	"<body><h1>202 Accepted</h1></body>"
	"</html>";
      const char no_content[] =
	"<html>"
	"<head><title>No Content</title></head>"
	"<body><h1>204 Content</h1></body>"
	"</html>";
      const char multiple_choices[] =
	"<html>"
	"<head><title>Multiple Choices</title></head>"
	"<body><h1>300 Multiple Choices</h1></body>"
	"</html>";
      const char moved_permanently[] =
	"<html>"
	"<head><title>Moved Permanently</title></head>"
	"<body><h1>301 Moved Permanently</h1></body>"
	"</html>";
      const char moved_temporarily[] =
	"<html>"
	"<head><title>Moved Temporarily</title></head>"
	"<body><h1>302 Moved Temporarily</h1></body>"
	"</html>";
      const char not_modified[] =
	"<html>"
	"<head><title>Not Modified</title></head>"
	"<body><h1>304 Not Modified</h1></body>"
	"</html>";
      const char bad_request[] =
	"<html>"
	"<head><title>Bad Request</title></head>"
	"<body><h1>400 Bad Request</h1></body>"
	"</html>";
      const char unauthorized[] =
	"<html>"
	"<head><title>Unauthorized</title></head>"
	"<body><h1>401 Unauthorized</h1></body>"
	"</html>";
      const char forbidden[] =
	"<html>"
	"<head><title>Forbidden</title></head>"
	"<body><h1>403 Forbidden</h1></body>"
	"</html>";
      const char not_found[] =
	"<html>"
	"<head><title>Not Found</title></head>"
	"<body><h1>404 Not Found</h1></body>"
	"</html>";
      const char internal_server_error[] =
	"<html>"
	"<head><title>Internal Server Error</title></head>"
	"<body><h1>500 Internal Server Error</h1></body>"
	"</html>";
      const char not_implemented[] =
	"<html>"
	"<head><title>Not Implemented</title></head>"
	"<body><h1>501 Not Implemented</h1></body>"
	"</html>";
      const char bad_gateway[] =
	"<html>"
	"<head><title>Bad Gateway</title></head>"
	"<body><h1>502 Bad Gateway</h1></body>"
	"</html>";
      const char service_unavailable[] =
	"<html>"
	"<head><title>Service Unavailable</title></head>"
	"<body><h1>503 Service Unavailable</h1></body>"
	"</html>";
      
      std::string to_string(Response::status_type status)
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
      
    } // namespace stock_replies
    
    Response Response::stock_reply(Response::status_type status)
    {
      Response rep;
      rep.status = status;
      rep.content = stock_replies::to_string(status);
      rep.headers.resize(2);
      rep.headers[0].name = "Content-Length";
      rep.headers[0].value = std::to_string(rep.content.size());
      rep.headers[1].name = "Content-Type";
      rep.headers[1].value = "text/html";
      return rep;
    }
  }
}

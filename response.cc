#include "response.hpp"
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

namespace status_strings 
{      
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
  
  std::string ResponseCodeToString(Response::ResponseCode status)
  {
    switch (status)
      {
      case Response::OK:
	return ok;
      case Response::CREATED:
	return created;
      case Response::ACCEPTED:
	return accepted;
      case Response::NO_CONTENT:
	return no_content;
      case Response::MULTIPLE_CHOICES:
	return multiple_choices;
      case Response::MOVED_PERMANENTLY:
	return moved_permanently;
      case Response::MOVED_TEMPORARILY:
	return moved_temporarily;
      case Response::NOT_MODIFIED:
	return not_modified;
      case Response::BAD_REQUEST:
	return bad_request;
      case Response::UNAUTHORIZED:
	return unauthorized;
      case Response::FORBIDDEN:
	return forbidden;
      case Response::NOT_FOUND:
	return not_found;
      case Response::INTERNAL_SERVER_ERROR:
	return internal_server_error;
      case Response::NOT_IMPLEMENTED:
	return not_implemented;
      case Response::BAD_GATEWAY:
	return bad_gateway;
      case Response::SERVICE_UNAVAILABLE:
	return service_unavailable;
      default: // for now, default is INTERNAL_SERVER_ERROR
	return internal_server_error;
      }
  }
} // namespace status_strings
    
void Response::SetStatus(const ResponseCode response_code)
{
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
	  return true;
	}
    }
  return false;
}

void Response::SetBody(const std::string& body)
{
  body_ = body;
}

std::string Response::ToString() const
{
  const std::string CRLF = "\r\n";
  std::string response_str = status_strings::ResponseCodeToString(response_code_) + CRLF;
  for (auto header : headers_)
    {
      response_str += header.first + ": " + header.second + CRLF;
    }
  response_str += CRLF; // Note that there is an extra CRLF between last header and body of response
  response_str += body_;
  return response_str;
}

Response Response::CreateStockResponse(Response::ResponseCode status)
{
  Response resp;
  resp.response_code_ = status;
  resp.body_ = status_strings::ResponseCodeToString(status);
  resp.headers_.push_back(std::make_pair("Content-Length", std::to_string(resp.body_.size())));
  resp.headers_.push_back(std::make_pair("Content-Type", "text/html"));            
  return resp;
}

void Response::ApplyGzip()
{
  std::string compressedString;
  boost::iostreams::filtering_ostream compressingStream;
  compressingStream.push(boost::iostreams::gzip_compressor(boost::iostreams::gzip_params(boost::iostreams::gzip::best_compression)));
  compressingStream.push(boost::iostreams::back_inserter(compressedString));
  compressingStream << body_;
  boost::iostreams::close(compressingStream);
  
  SetBody(compressedString);
  SetHeader("Content-Length", std::to_string(compressedString.size()));
  AddHeader("Content-Encoding", "gzip");      
}

std::string Response::GetBody() const
{
  return body_;
}

Response::ResponseCode Response::ReturnResponseCode() const
{
  return response_code_;
}

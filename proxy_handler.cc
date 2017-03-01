#include "proxy_handler.hpp"
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

using boost::asio::ip::tcp;


namespace http{
namespace server{
    
RequestHandler::Status ProxyHandler::Init(const std::string& uri_prefix, const NginxConfig& config)
{
    uri_prefix_ = uri_prefix;
    bool remote_host_found = false;

    if (config.statements_.size() != 1)
        return RequestHandler::Status::NOT_OK;
    else
    {
        for (const auto& statement : config.statements_)
        {
            if (statement->tokens_[0] == "remote_host" && statement->tokens_.size() == 2)
            {
	        remote_host_whole_url = statement->tokens_[1];
                remote_host_found = parse_remote_url(remote_host_whole_url);
		if(remote_host_found == true)
		    return RequestHandler::Status::OK;
                else
		{    return RequestHandler::Status::NOT_OK;}  
	    }
            else 
                {return RequestHandler::Status::NOT_OK;}
        }
	return RequestHandler::Status::NOT_OK;
    }
}

bool ProxyHandler::parse_remote_url(std::string remote_host_url)
{
    std::size_t slash_found = remote_host_url.find("//");
    if(slash_found == std::string::npos)
	return false;
    protocol_ = remote_host_url.substr(0, slash_found-1);

    std::size_t host_found = remote_host_url.find('/', slash_found + 2);
    if(host_found != std::string::npos) 
    {
        host_url_ = remote_host_url.substr(slash_found + 2, host_found - slash_found - 2);
	path_ = remote_host_url.substr(host_found);
    }
    else 
    {
        host_url_ = remote_host_url.substr(slash_found + 2);
	path_ = "";
    }

    return true;	
}

bool ProxyHandler::parse_remote_response(std::string remote_response)
{
    std::size_t status_found = remote_response.find("\r\n");
    if(status_found == std::string::npos)
	return false;
    response_status = remote_response.substr(0, status_found + 1);
    rest = remote_response.substr(status_found + 2);        

    std::size_t header_found = rest.find("\r\n\r\n");
    if(header_found == std::string::npos)
	return false;
    response_headers = rest.substr(0, header_found + 3);
    response_body = rest.substr(header_found + 4);

    read_header(response_headers);  

    return true;
    	
}

bool ProxyHandler::read_header(std::string headers)
{
  std::string temp_headers = headers;
  std::string line;
  while(temp_headers.size() > 0 && temp_headers != "\r" && temp_headers != "\n")
  {
    std::size_t header_found = temp_headers.find("\r\n", 0);
    if (header_found != std::string::npos){
        line = temp_headers.substr(0, header_found+1);
	temp_headers = temp_headers.substr(header_found+2);
    }
    std::stringstream ssHeader(line);

    std::string headerName;
    std::getline(ssHeader, headerName, ':');

    ssHeader >> std::ws; 
    std::string value;
    std::getline(ssHeader, value, '\r');
    
    std::pair<std::string, std::string> header_pair(headerName, value);
    this->headers_.push_back(header_pair);
  }
  return 1;
	
}

bool ProxyHandler::url_decode(const std::string& in, std::string& out)
{
    out.clear();
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i)
    {
	if (in[i] == '%')
	{
	    if (i + 3 <= in.size())
	    {
		int value = 0;
		std::istringstream is(in.substr(i + 1, 2));
		if (is >> std::hex >> value)
		{
		    out += static_cast<char>(value);
		    i += 2;
		}
		else
		{
		    return false;
		}
	    }
	    else
	    {
		return false;
	    }
	}
	else if (in[i] == '+')
	{
	    out += ' ';
	}
	else
	{
	    out += in[i];
	}
    }
    return true;
} 
    

RequestHandler::Status ProxyHandler::HandleRequest(const Request& request, Response* response)
{
    std::string request_uri = request.uri();
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(host_url_, "80");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::resolver::iterator iter = endpoint_iterator;
    tcp::resolver::iterator end;

    while (iter != end)
    {
      tcp::endpoint endpoint = *iter++;
      std::cout << endpoint << std::endl;
    }

    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    std::cout << "Successfully connected!\n";

    std::string request_string = std::string("GET ") + path_ + request_uri.substr(uri_prefix_.size()-1) + " HTTP/1.1\r\n" + "Host: " + host_url_ + ":" + "80";


    request_string += std::string("\r\nConnection: keep-alive\r\n") +
                      "Accept: text/html\r\n" +
                      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n" +
                      "Accept-Encoding: gzip, deflate, sdch\r\n" +
                      "Accept-Language: en-US,en;q=0.8\r\n" +
                      "\r\n";
                                     
    std::cout << request_string<<std::endl;

    // Write request to remote server
    socket.write_some(boost::asio::buffer(request_string, request_string.size()));

    std::string remote_response;

    while(1) {
      
        boost::array<char, 4096> buf;
        boost::system::error_code error;

	//read the response from remote server
        size_t len = socket.read_some(boost::asio::buffer(buf), error);

        if (error == boost::asio::error::eof) {
            std::cout <<"Exited cleanly\n";
            break; // Connection closed cleanly by peer.
        }
        else if (error)
            throw boost::system::system_error(error); // Some other error.

	
        std::cout.write(buf.data(), len);
        remote_response += std::string(buf.data(), len);

        
    }
	std::cout<<"out of loop";
    bool remote_response_status;
    remote_response_status = parse_remote_response(remote_response);
    if (remote_response_status == false)
        return RequestHandler::Status::NOT_OK;

    response->SetStatus(Response::ResponseCode::ok);
    for (std::vector<std::pair<std::string, std::string>>::const_iterator it = headers_.begin(); it != headers_.end(); it++)
    {
        response->AddHeader(it->first, it->second);
    }
    //response->AddHeader("Content-Type", "text/html");
    //response->AddHeader("Content-Encoding", "gzip");
    //response->SetBody(request.raw_request());
    response->SetBody(response_body);
    headers_.clear();

    return Status::OK;
}
std::string ProxyHandler::getPrefix()
{
	return uri_prefix_;
}
std::string ProxyHandler::getWholeURL()
{
	return remote_host_whole_url;
}
std::string ProxyHandler::getProtocol()
{
	return protocol_;
}
std::string ProxyHandler::getHostURL()
{
	return host_url_;
}
std::string ProxyHandler::getPath()
{
	return path_;
}

} // namespace server
} // namespace http

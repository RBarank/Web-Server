#include "static_handler.hpp"
#include "cpp-markdown/markdown.h"
#include <fstream>
#include <sstream>
#include <iostream>

RequestHandler::Status StaticHandler::Init(const std::string& uri_prefix, const NginxConfig& config)
{
  uri_prefix_ = uri_prefix;
  for (const auto& statement : config.statements_)
    {
      if (statement->tokens_[0] == "root" && statement->tokens_.size() == 2)
	{
	  root_path_ = statement->tokens_[1];
	}
    }
  return RequestHandler::OK;
}

bool StaticHandler::UrlDecode(const std::string& in, std::string& out) const
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


RequestHandler::Status StaticHandler::HandleRequest(const Request& request, Response* response)
{
  if (request.GetUri().length() == 0)
    {
      *response = Response::CreateStockResponse(Response::BAD_REQUEST);
      return RequestHandler::NOT_OK;
    }
  size_t second_slash = request.GetUri().substr(1).find_first_of("/");
  std::string request_base = request.GetUri().substr(0,second_slash + 1);
  std::string file_path = request.GetUri().substr(request_base.length());
  
  std::string request_path;
  if (!UrlDecode(file_path, request_path))
    {
      *response = Response::CreateStockResponse(Response::BAD_REQUEST);
      return RequestHandler::NOT_OK;
    }
  
  // Request path must be absolute and not contain "..".
  if (request_path.empty() || request_path[0] != '/'
      || (request_path.find("..") != std::string::npos))
    {
      *response = Response::CreateStockResponse(Response::BAD_REQUEST);
      return RequestHandler::NOT_OK;
    }
  
  // TODO: this code in the if statement below is old, remove it and handle this case differently.
  // If path ends in slash (i.e. is a directory) then add "index.html". <-- replace this behavior
  if (request_path[request_path.size() - 1] == '/')
    {
      request_path += "index.html";
    }
  
  std::size_t last_slash_pos = request_path.find_last_of("/");
  std::size_t last_dot_pos = request_path.find_last_of(".");
  std::string extension;
  if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
    {
      extension = request_path.substr(last_dot_pos + 1);
    }
  else
    {
      *response = Response::CreateStockResponse(Response::BAD_REQUEST);
      return RequestHandler::NOT_OK;
    }
  
  // Open the file to send back.
  std::string full_path = root_path_ + request_path;
  full_path = full_path.substr(1);
  std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
  if (!is)
    {
      *response = Response::CreateStockResponse(Response::NOT_FOUND);
      return RequestHandler::FILE_NOT_FOUND;
    }
  
  // Fill out the reply to be sent to the client.
  response->SetStatus(Response::OK);
  char buf[512];
  std::string content;
  while (is.read(buf, sizeof(buf)).gcount() > 0)
    {
      content.append(buf, is.gcount());
      memset(buf, 0, sizeof(buf));
    }
  
  // Handle markdown files
  if (extension == "md")
    {
      std::string temp = MarkdownToHtml(content);
      content = temp;
    }
  
  response->SetBody(content); 
  response->AddHeader("Content-Length", std::to_string(content.size()));
  response->AddHeader("Content-Type", mime_types::ExtensionToType(extension)); 
  return RequestHandler::OK;
}


std::string StaticHandler::MarkdownToHtml(const std::string& content) const
{
  // Use the cpp-markdown library to handle markdown files
  markdown::Document md_doc;
  md_doc.read(content);
  std::ostringstream oss;
  md_doc.write(oss);
  
  return oss.str();
}

#include "status_handler.hpp"
#include "server_info.hpp"
#include <vector>


std::string StatusHandler::CreateStatusString() const 
{
  /*
    Write a new request handler that displays information on the status of the web server, such as:
    How many requests has the server received? Break this down by URL requested and the response code returned (200, 400, etc.).
    What request handlers exist, and for what URL prefixes?
    In your config file, configure the status handler for the "/status" URI.
  */
  
  std::string status_string;
  
  status_string += "SERVER STATUS\n\n";
  status_string += "Number of requests received: " + std::to_string(ServerInfo::getInstance().get_number_of_requests());
  status_string += "\n\n";
  
  std::vector<HandlerInfo> handler_info = ServerInfo::getInstance().ret_handler_info();
  std::vector<RequestInfo> request_info = ServerInfo::getInstance().ret_request_info();
  
  status_string += "HANDLERS\n";
  status_string += "Name -> URL Prefix:\n";
  for (size_t i = 0; i < handler_info.size(); i++)
    {
      status_string += handler_info[i].type_of_handler;
      status_string += " -> ";
      status_string += handler_info[i].url_prefix;
      status_string += "\n";
    }
  
  status_string += "\n";
  
  status_string += "REQUESTS RECEIVED\n";
  status_string += "URL -> Response Code:\n";
  for (size_t i = 0; i < request_info.size(); i++)
    {
      status_string += request_info[i].url;
      status_string += " -> ";
      status_string += std::to_string(request_info[i].rc);
      status_string += "\n";
    }
  
  status_string += "\n";
  
  return status_string;  
}

RequestHandler::Status StatusHandler::HandleRequest(const Request& request, Response* response)
{
  response->SetStatus(Response::OK);

  std::string body = CreateStatusString();
  response->AddHeader("Content-Length", std::to_string(body.size()));
  response->AddHeader("Content-Type", "text/plain");
  response->SetBody(body);

  return RequestHandler::OK;
}

RequestHandler::Status StatusHandler::Init(const std::string& uri_prefix, const NginxConfig& config)
{
  return RequestHandler::OK;
}



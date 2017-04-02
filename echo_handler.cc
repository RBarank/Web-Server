#include "echo_handler.hpp"


RequestHandler::Status EchoHandler::HandleRequest(const Request& request, Response* response)
{    
  response->SetStatus(Response::ok);
  response->AddHeader("Content-Length", std::to_string(request.GetRawRequest().size()));
  response->AddHeader("Content-Type", "text/plain");
  response->SetBody(request.GetRawRequest());
  return RequestHandler::OK;
}

RequestHandler::Status EchoHandler::Init(const std::string& uri_prefix, const NginxConfig& config)
{
  return RequestHandler::OK;
}

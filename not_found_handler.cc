#include "not_found_handler.hpp"


RequestHandler::Status NotFoundHandler::HandleRequest(const Request& request, Response* response)
{
  response->SetStatus(Response::not_found);
  *response = Response::stock_response(Response::not_found);
  return RequestHandler::OK;
}

RequestHandler::Status NotFoundHandler::Init(const std::string& uri_prefix, const NginxConfig& config)
{
  return RequestHandler::OK;
}

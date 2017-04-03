#include "not_found_handler.hpp"


RequestHandler::Status NotFoundHandler::HandleRequest(const Request& request, Response* response)
{
  // delete old response, replace with a stock not found response
  // TODO: use a unique ptr to response?
  delete response; 
  *response = Response::CreateStockResponse(Response::NOT_FOUND);
  return RequestHandler::OK;
}

RequestHandler::Status NotFoundHandler::Init(const std::string& uri_prefix, const NginxConfig& config)
{
  return RequestHandler::OK;
}

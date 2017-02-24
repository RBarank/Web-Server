#include "not_found_handler.hpp"

namespace http{
  namespace server{

    request_handler::Status NotFoundHandler::HandleRequest(const Request& request, Response* response){
        response->SetStatus(Response::not_found);
//      response->AddHeader("Content-Length", std::to_string(request.raw_request().size()));
//      response->AddHeader("Content-Type", "text/plain");
//      response->SetBody(request.raw_request());
        *response = Response::stock_response(Response::not_found);
        return request_handler::OK;
    }

    request_handler::Status NotFoundHandler::Init(const std::string& uri_prefix, const NginxConfig& config)
    {
        return request_handler::OK;
    }
   
  }
}

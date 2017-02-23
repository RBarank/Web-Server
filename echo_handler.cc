#include "echo_handler.hpp"

namespace http{
  namespace server{
    /*
    bool echo_handler::handle_request(const request& request_, reply& reply_){
      reply_.content.append(request_.content, request_.length);
      reply_.status = reply::ok;
      reply_.headers.resize(2);
      reply_.headers[0].name = "Content-Length";
      reply_.headers[0].value = std::to_string(reply_.content.size());
      reply_.headers[1].name = "Content-Type";
      reply_.headers[1].value = "text/plain";
      return true;
      }
    */


    request_handler::Status echo_handler::HandleRequest(const Request& request, Response* response){
      
      response->SetStatus(Response::ok);
      response->AddHeader("Content-Length", std::to_string(request.raw_request().size()));
      response->AddHeader("Content-Type", "text/plain");
      response->SetBody(request.raw_request());
      return request_handler::OK;
    }

    request_handler::Status echo_handler::Init(const std::string& uri_prefix, const NginxConfig& config)
    {
      return request_handler::OK;
    }
   
  }
}

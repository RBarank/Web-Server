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

    Status Init(const std::string& uri_prefix, const NginxConfig& config)
    {
      return request_handler::OK;
    }
   
  }
}

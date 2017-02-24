#include "StatusHandler.hpp"
#include "server_info.hpp"
#include <vector>

std::string setBody();

namespace http{
  namespace server{
    std::string setBody() {
        /*
        Write a new request handler that displays information on the status of the web server, such as:
        How many requests has the server received? Break this down by URL requested and the response code returned (200, 400, etc.).
        What request handlers exist, and for what URL prefixes?
            In your config file, configure the status handler for the "/status" URI.
        */
    
        std::string ret;
        
        ret += "STATUS\n\n";
        ret += "Number of requests received: " + std::to_string(ServerInfo::getInstance().get_number_of_requests());
        ret += "\n";
        
        std::vector<HandlerInfo> handler_info = ServerInfo::getInstance().ret_handler_info();
        std::vector<RequestInfo> request_info = ServerInfo::getInstance().ret_request_info();
        
        ret += "Handlers :\n";
        for (int i =0 ; i <handler_info.size();i++)
        {
            ret += "Type of handler : ";
            ret += handler_info[i].type_of_handler;
            ret += ". URL prefix : ";
            ret += handler_info[i].url_prefix;
            ret += "\n";
        }
        
        ret += "\n";
        
        ret += "Requests :\n";
        for (int i =0 ; i <request_info.size();i++)
        {
            ret += "URL : ";
            ret += request_info[i].url;
            ret += " -> Response Code : ";
            ret += std::to_string(request_info[i].rc);
            ret += "\n";
        }
        
        ret += "\n";
        
        return ret;
    
    }

    request_handler::Status StatusHandler::HandleRequest(const Request& request, Response* response){
        response->SetStatus(Response::ok);
        
        std::string body = setBody();
        response->AddHeader("Content-Length", std::to_string(body.size()));
        response->AddHeader("Content-Type", "text/plain");
        response->SetBody(body);
        return request_handler::OK;
    }

    request_handler::Status StatusHandler::Init(const std::string& uri_prefix, const NginxConfig& config)
    {
        return request_handler::OK;
    }
   
  }
}



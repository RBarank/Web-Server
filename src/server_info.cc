#include "server_info.hpp"



namespace http{
    namespace server{
        ServerInfo& ServerInfo::getInstance()
        {
            static ServerInfo instance;
            return instance;
        }
        int ServerInfo::get_number_of_requests()
        {
            return int(request_info.size());
        }
        void ServerInfo::append_request(std::string url, Response::ResponseCode rc)
        {
            RequestInfo tmp;
            tmp.url = url;
            tmp.rc = rc;
            request_info.push_back(tmp);
        }
        void ServerInfo::append_handler(std::string type_of_handler, std::string url_prefix)
        {
            HandlerInfo tmp;
            tmp.type_of_handler = type_of_handler;
            tmp.url_prefix = url_prefix;
            handler_info.push_back(tmp);
        }
        void ServerInfo::append_request(RequestInfo ri)
        {
            request_info.push_back(ri);
        }
        void ServerInfo::append_handler(HandlerInfo hi)
        {
            handler_info.push_back(hi);
        }
        void ServerInfo::lock()
        {
            mutex_.lock();
        }
        void ServerInfo::unlock()
        {
            mutex_.unlock();
        }
    }
}

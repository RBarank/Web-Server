#ifndef STATUS_HANDLER_HPP
#define STATUS_HANDLER_HPP

#include <string>
#include <vector>
#include "request.hpp"
#include "response.hpp"
#include "request_handler.hpp"


class StatusHandler : public RequestHandler
{
public:
  virtual Status Init(const std::string& uri_prefix,
		      const NginxConfig& config);
  virtual Status HandleRequest(const Request& request,
			       Response* response);
};

REGISTER_REQUEST_HANDLER(StatusHandler);


#endif // ECHO_HANDLER_HPP

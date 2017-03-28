#include "gtest/gtest.h"
#include "response.hpp"
#include <string>

namespace http{
  namespace server{


TEST(ResponseTest2, EmptyResponse) 
{
  Response test_response;
  EXPECT_NO_THROW(test_response.SetStatus(Response::ok));
  EXPECT_NO_THROW(test_response.SetBody("Testing"));
  EXPECT_NO_THROW(test_response.AddHeader("Header 1", "Value 1"));
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, BadRequest) 
{
  Response test_response;
  EXPECT_NO_THROW(test_response = Response::stock_response(Response::bad_request));
  EXPECT_EQ(test_response.ret_response_code(), Response::bad_request);
  EXPECT_NO_THROW(test_response.ToString());
}


TEST(StockResponse, OK) 
{
  Response test_response;
  test_response = Response::stock_response(Response::ok);
  EXPECT_EQ(test_response.ret_response_code(), Response::ok);
  EXPECT_NO_THROW(test_response.ToString());

}

TEST(StockResponse, BadGateway) 
{
  Response test_response;
  test_response = Response::stock_response(Response::bad_gateway);
  EXPECT_EQ(test_response.ret_response_code(), Response::bad_gateway);
  EXPECT_NO_THROW(test_response.ToString());

}

TEST(StockResponse, NotModified) 
{
  Response test_response;
  test_response = Response::stock_response(Response::not_modified);
  EXPECT_EQ(test_response.ret_response_code(), Response::not_modified);
  EXPECT_NO_THROW(test_response.ToString());

}

TEST(StockResponse, NotFound) 
{
  Response test_response;
  test_response = Response::stock_response(Response::not_found);
  EXPECT_EQ(test_response.ret_response_code(), Response::not_found);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, Created) 
{
  Response test_response;
  test_response = Response::stock_response(Response::created);
  EXPECT_EQ(test_response.ret_response_code(), Response::created);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, Accepted) 
{
  Response test_response;
  test_response = Response::stock_response(Response::accepted);
  EXPECT_EQ(test_response.ret_response_code(), Response::accepted);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, NoContent) 
{
  Response test_response;
  test_response = Response::stock_response(Response::no_content);
  EXPECT_EQ(test_response.ret_response_code(), Response::no_content);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, MultipleChoices) 
{
  Response test_response;
  test_response = Response::stock_response(Response::multiple_choices);
  EXPECT_EQ(test_response.ret_response_code(), Response::multiple_choices);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, Forbidden) 
{
  Response test_response;
  test_response = Response::stock_response(Response::forbidden);
  EXPECT_EQ(test_response.ret_response_code(), Response::forbidden);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, MovedPerm) 
{
  Response test_response;
  test_response = Response::stock_response(Response::moved_permanently);
  EXPECT_EQ(test_response.ret_response_code(), Response::moved_permanently);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, MovedTemp) 
{
  Response test_response;
  test_response = Response::stock_response(Response::moved_temporarily);
  EXPECT_EQ(test_response.ret_response_code(), Response::moved_temporarily);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, Unauthorized) 
{
  Response test_response;
  test_response = Response::stock_response(Response::unauthorized);
  EXPECT_EQ(test_response.ret_response_code(), Response::unauthorized);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, InternalError) 
{
  Response test_response;
  test_response = Response::stock_response(Response::internal_server_error);
  EXPECT_EQ(test_response.ret_response_code(), Response::internal_server_error);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, NotImplemented) 
{
  Response test_response;
  test_response = Response::stock_response(Response::not_implemented);
  EXPECT_EQ(test_response.ret_response_code(), Response::not_implemented);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, ServiceUnavailable) 
{
  Response test_response;
  test_response = Response::stock_response(Response::service_unavailable);
  EXPECT_EQ(test_response.ret_response_code(), Response::service_unavailable);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(Response, Compression) 
{
  Response test_response;
  test_response = Response::stock_response(Response::ok);
  EXPECT_NO_THROW(test_response.ApplyGzip());
}
    

  } // namespace server
} // namespace http

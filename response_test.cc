#include "gtest/gtest.h"
#include "response.hpp"
#include <string>


TEST(ResponseTest2, EmptyResponse) 
{
  Response test_response;
  EXPECT_NO_THROW(test_response.SetStatus(Response::OK));
  EXPECT_NO_THROW(test_response.SetBody("Testing"));
  EXPECT_NO_THROW(test_response.AddHeader("Header 1", "Value 1"));
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, BadRequest) 
{
  Response test_response;
  EXPECT_NO_THROW(test_response = Response::CreateStockResponse(Response::BAD_REQUEST));
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::BAD_REQUEST);
  EXPECT_NO_THROW(test_response.ToString());
}


TEST(StockResponse, OK) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::OK);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::OK);
  EXPECT_NO_THROW(test_response.ToString());

}

TEST(StockResponse, BadGateway) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::BAD_GATEWAY);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::BAD_GATEWAY);
  EXPECT_NO_THROW(test_response.ToString());

}

TEST(StockResponse, NotModified) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::NOT_MODIFIED);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::NOT_MODIFIED);
  EXPECT_NO_THROW(test_response.ToString());

}

TEST(StockResponse, NotFound) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::NOT_FOUND);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::NOT_FOUND);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, Created) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::CREATED);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::CREATED);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, Accepted) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::ACCEPTED);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::ACCEPTED);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, NoContent) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::NO_CONTENT);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::NO_CONTENT);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, MultipleChoices) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::MULTIPLE_CHOICES);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::MULTIPLE_CHOICES);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, Forbidden) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::FORBIDDEN);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::FORBIDDEN);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, MovedPerm) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::MOVED_PERMANENTLY);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::MOVED_PERMANENTLY);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, MovedTemp) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::MOVED_TEMPORARILY);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::MOVED_TEMPORARILY);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, Unauthorized) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::UNAUTHORIZED);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::UNAUTHORIZED);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, InternalError) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::INTERNAL_SERVER_ERROR);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::INTERNAL_SERVER_ERROR);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, NotImplemented) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::NOT_IMPLEMENTED);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::NOT_IMPLEMENTED);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockResponse, ServiceUnavailable) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::SERVICE_UNAVAILABLE);
  EXPECT_EQ(test_response.ReturnResponseCode(), Response::SERVICE_UNAVAILABLE);
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(Response, Compression) 
{
  Response test_response;
  test_response = Response::CreateStockResponse(Response::OK);
  EXPECT_NO_THROW(test_response.ApplyGzip());
}
    

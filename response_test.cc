#include "gtest/gtest.h"
#include "response.hpp"
#include <string>

namespace http{
  namespace server{


TEST(ReplyTest2, EmptyResponse) 
{
  Response test_response;
  EXPECT_NO_THROW(test_response.SetStatus(Response::ok));
  EXPECT_NO_THROW(test_response.SetBody("Testing"));
  EXPECT_NO_THROW(test_response.AddHeader("Header 1", "Value 1"));
  EXPECT_NO_THROW(test_response.ToString());
}

TEST(StockReply, BadRequest) 
{
  Response test_response;
  EXPECT_NO_THROW(test_response = Response::stock_response(Response::bad_request));
  EXPECT_NO_THROW(test_response.ToString());
}

    /*
TEST(StockReply, OK) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::ok);
  EXPECT_EQ(test_reply.status, reply::ok);
  EXPECT_NO_THROW(test_reply.to_buffers());

}

TEST(StockReply, BadGateway) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::bad_gateway);
  EXPECT_EQ(test_reply.status, reply::bad_gateway);
  EXPECT_NO_THROW(test_reply.to_buffers());

}

TEST(StockReply, NotModified) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::not_modified);
  EXPECT_EQ(test_reply.status, reply::not_modified);
  EXPECT_NO_THROW(test_reply.to_buffers());

}

TEST(StockReply, NotFound) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::not_found);
  EXPECT_EQ(test_reply.status, reply::not_found);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, Created) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::created);
  EXPECT_EQ(test_reply.status, reply::created);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, Accepted) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::accepted);
  EXPECT_EQ(test_reply.status, reply::accepted);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, NoContent) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::no_content);
  EXPECT_EQ(test_reply.status, reply::no_content);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, MultipleChoices) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::multiple_choices);
  EXPECT_EQ(test_reply.status, reply::multiple_choices);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, Forbidden) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::forbidden);
  EXPECT_EQ(test_reply.status, reply::forbidden);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, MovedPerm) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::moved_permanently);
  EXPECT_EQ(test_reply.status, reply::moved_permanently);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, MovedTemp) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::moved_temporarily);
  EXPECT_EQ(test_reply.status, reply::moved_temporarily);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, Unauthorized) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::unauthorized);
  EXPECT_EQ(test_reply.status, reply::unauthorized);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, InternalError) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::internal_server_error);
  EXPECT_EQ(test_reply.status, reply::internal_server_error);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, NotImplemented) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::not_implemented);
  EXPECT_EQ(test_reply.status, reply::not_implemented);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, ServiceUnavailable) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::service_unavailable);
  EXPECT_EQ(test_reply.status, reply::service_unavailable);
  EXPECT_NO_THROW(test_reply.to_buffers());
}
    */

  } // namespace server
} // namespace http

#include "gtest/gtest.h"
#include "reply.hpp"
#include <string>

namespace http{
  namespace server{


TEST(ReplyTest2, EmptyReply) 
{
  reply test_reply;
  EXPECT_EQ(test_reply.content, "");
  EXPECT_EQ(test_reply.headers.size(), 0);
  EXPECT_NO_THROW(test_reply.to_buffers());
}

TEST(StockReply, BadRequest) 
{
  reply test_reply;
  test_reply = reply::stock_reply(reply::bad_request);
  EXPECT_EQ(test_reply.status, reply::bad_request);
  EXPECT_EQ(test_reply.content,
	    "<html><head><title>Bad Request</title></head><body><h1>400 Bad Request</h1></body></html>");
  EXPECT_NO_THROW(test_reply.to_buffers());
}

 
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


  } // namespace server
} // namespace http

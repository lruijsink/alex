#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/any.h"

TEST(single, true_unless_eof)
{
  EXPECT_TRUE(alex::parse("a", alex::any()));
  EXPECT_FALSE(alex::parse("", alex::any()));
}

TEST(single, consumes_from_stream)
{
  EXPECT_FALSE(alex::parse("a", alex::any() + alex::any()));
}

#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(basic, always_matches)
{
  EXPECT_TRUE(alex::parser().match("foo", alex::optional("foo")));
  EXPECT_TRUE(alex::parser().match("bar", alex::optional("foo")));
}

TEST(basic, consumes_only_match)
{
  EXPECT_TRUE (alex::parser().match("x", alex::optional("x") + alex::eof()));
  EXPECT_FALSE(alex::parser().match("y", alex::optional("x") + alex::eof()));
}

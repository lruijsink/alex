#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(basic, always_matches)
{
  EXPECT_TRUE (alex::parser().match("foo", alex::optional("foo")));
  EXPECT_FALSE(alex::parser().match("bar", alex::optional("foo")));
  EXPECT_TRUE (alex::parser().match("bar", alex::optional("foo") + "bar"));
}

TEST(basic, consumes_only_match)
{
  EXPECT_TRUE (alex::parser().match("x", alex::optional("x")));
  EXPECT_FALSE(alex::parser().match("y", alex::optional("x")));
}

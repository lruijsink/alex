#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/literal.h"
#include "alex/eof.h"

#include "alex/optional.h"

TEST(basic, always_matches)
{
  EXPECT_TRUE(alex::match("foo", alex::optional("foo")));
  EXPECT_TRUE(alex::match("bar", alex::optional("foo")));
}

TEST(basic, consumes_only_match)
{
  EXPECT_TRUE (alex::match("x", alex::optional("x") + alex::eof()));
  EXPECT_FALSE(alex::match("y", alex::optional("x") + alex::eof()));
}

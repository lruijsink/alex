#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/literal.h"
#include "alex/eof.h"

#include "alex/empty.h"

TEST(basic, matches)
{
  EXPECT_TRUE (alex::parse("x", alex::empty_true()));
  EXPECT_FALSE(alex::parse("x", alex::empty_false()));
}

TEST(basic, does_not_consume)
{
  EXPECT_TRUE (alex::parse("x", alex::empty_true() + 'x' + alex::eof()));
  EXPECT_FALSE(alex::parse("x", alex::empty_true() + alex::eof()));
}

TEST(basic, eof_still_true)
{
  EXPECT_TRUE(alex::parse("", alex::empty_true()));
}

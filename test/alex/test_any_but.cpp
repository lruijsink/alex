#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/literal.h"
#include "alex/eof.h"

#include "alex/any_but.h"

TEST(single, matches)
{
  EXPECT_TRUE (alex::match("X", alex::any_but('a')));
  EXPECT_FALSE(alex::match("a", alex::any_but('a')));
}

TEST(single, consumes)
{
  EXPECT_TRUE(alex::match("X", alex::any_but('a') + alex::eof()));
}

TEST(single, is_not_eof)
{
  EXPECT_FALSE(alex::match("", alex::any_but('a')));
}


#include "gtest/gtest.h"
#include "alex/alex.h"

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


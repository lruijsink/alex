#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(single, matches)
{
  EXPECT_TRUE (alex::match("a", alex::any()));
}

TEST(single, consumes)
{
  EXPECT_TRUE(alex::match("a", alex::any() + alex::eof()));
}

TEST(single, is_not_eof)
{
  EXPECT_FALSE(alex::match("", alex::any()));
}


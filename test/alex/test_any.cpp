#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(single, matches)
{
  EXPECT_TRUE(alex::parser().match("a", alex::any()));
}

TEST(single, is_not_eof)
{
  EXPECT_FALSE(alex::parser().match("", alex::any()));
}


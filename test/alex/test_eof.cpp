#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(single, true_if_eof)
{
  EXPECT_TRUE (alex::match("",  alex::eof()));
  EXPECT_FALSE(alex::match("a", alex::eof()));
}

TEST(single, chains)
{
  EXPECT_TRUE (alex::match("", alex::eof() + alex::eof()));
}

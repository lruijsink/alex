#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(single, true_if_eof)
{
  EXPECT_TRUE (alex::parser().match("",  alex::eof()));
  EXPECT_FALSE(alex::parser().match("a", alex::eof()));
}

TEST(single, chains)
{
  EXPECT_TRUE (alex::parser().match("", alex::eof() + alex::eof()));
}

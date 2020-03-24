#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/literal.h"

#include "alex/eof.h"

TEST(single, true_if_eof)
{
  EXPECT_TRUE (alex::parse("",  alex::eof()));
  EXPECT_FALSE(alex::parse("a", alex::eof()));
}

TEST(single, chains)
{
  EXPECT_TRUE (alex::parse("", alex::eof() + alex::eof()));
}

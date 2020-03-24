#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/literal.h"
#include "alex/eof.h"

#include "alex/any.h"

TEST(single, matches)
{
  EXPECT_TRUE (alex::parse("a", alex::any()));
}

TEST(single, consumes)
{
  EXPECT_TRUE(alex::parse("a", alex::any() + alex::eof()));
}

TEST(single, is_not_eof)
{
  EXPECT_FALSE(alex::parse("", alex::any()));
}


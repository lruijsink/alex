#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/literal.h"
#include "alex/eof.h"

#include "alex/fixed.h"

TEST(basic, matches)
{
  EXPECT_TRUE (alex::parse("x", alex::grammar<std::true_type>()));
  EXPECT_FALSE(alex::parse("x", alex::grammar<std::false_type>()));
}

TEST(basic, does_not_consume)
{
  EXPECT_TRUE (alex::parse("x", alex::grammar<std::true_type>() + 'x' + alex::eof()));
  EXPECT_FALSE(alex::parse("x", alex::grammar<std::true_type>() + alex::eof()));
}

TEST(basic, eof_still_true)
{
  EXPECT_TRUE(alex::parse("", alex::grammar<std::true_type>()));
}

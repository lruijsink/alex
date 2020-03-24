#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/from_to.h"

TEST(bounds, bounds_are_inclusive)
{
  EXPECT_TRUE(alex::parse("1", alex::from_to('1', '3')));
  EXPECT_TRUE(alex::parse("2", alex::from_to('1', '3')));
  EXPECT_TRUE(alex::parse("3", alex::from_to('1', '3')));
}

TEST(bounds, out_of_bounds)
{
  EXPECT_FALSE(alex::parse("0", alex::from_to('1', '3')));
  EXPECT_FALSE(alex::parse("4", alex::from_to('1', '3')));
}

TEST(consumes, consumes_1)
{
  EXPECT_TRUE (alex::parse("12", alex::from_to('1', '3') + alex::from_to('1', '3')));
  EXPECT_FALSE(alex::parse("1",  alex::from_to('1', '3') + alex::from_to('1', '3')));
}

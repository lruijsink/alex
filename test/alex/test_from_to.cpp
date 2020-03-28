#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(bounds, bounds_are_inclusive)
{
  EXPECT_TRUE(alex::parser().match("1", alex::from_to('1', '3')));
  EXPECT_TRUE(alex::parser().match("2", alex::from_to('1', '3')));
  EXPECT_TRUE(alex::parser().match("3", alex::from_to('1', '3')));
}

TEST(bounds, out_of_bounds)
{
  EXPECT_FALSE(alex::parser().match("0", alex::from_to('1', '3')));
  EXPECT_FALSE(alex::parser().match("4", alex::from_to('1', '3')));
}

TEST(consumes, consumes_1)
{
  EXPECT_TRUE (alex::parser().match("11", alex::from_to('1', '3') + '1'));
}

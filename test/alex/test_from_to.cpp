#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(bounds, bounds_are_inclusive)
{
  EXPECT_TRUE(alex::match("1", alex::from_to('1', '3')));
  EXPECT_TRUE(alex::match("2", alex::from_to('1', '3')));
  EXPECT_TRUE(alex::match("3", alex::from_to('1', '3')));
}

TEST(bounds, out_of_bounds)
{
  EXPECT_FALSE(alex::match("0", alex::from_to('1', '3')));
  EXPECT_FALSE(alex::match("4", alex::from_to('1', '3')));
}

TEST(consumes, consumes_1)
{
  EXPECT_TRUE (alex::match("11", alex::from_to('1', '3') + '1' + alex::eof()));
  EXPECT_FALSE(alex::match("1",  alex::from_to('1', '3') + '1'));
}

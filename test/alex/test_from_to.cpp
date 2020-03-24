#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/literal.h"
#include "alex/eof.h"

#include "alex/from_to.h"

TEST(bounds, bounds_are_inclusive)
{
  EXPECT_TRUE(alex::parse("1", alex::from('1').to('3')));
  EXPECT_TRUE(alex::parse("2", alex::from('1').to('3')));
  EXPECT_TRUE(alex::parse("3", alex::from('1').to('3')));
}

TEST(bounds, out_of_bounds)
{
  EXPECT_FALSE(alex::parse("0", alex::from('1').to('3')));
  EXPECT_FALSE(alex::parse("4", alex::from('1').to('3')));
}

TEST(consumes, consumes_1)
{
  EXPECT_TRUE (alex::parse("11", alex::from('1').to('3') + '1' + alex::eof()));
  EXPECT_FALSE(alex::parse("1",  alex::from('1').to('3') + '1'));
}

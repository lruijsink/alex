#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/literal.h"
#include "alex/eof.h"

#include "alex/from_to.h"

TEST(bounds, bounds_are_inclusive)
{
  EXPECT_TRUE(alex::match("1", alex::from('1').to('3')));
  EXPECT_TRUE(alex::match("2", alex::from('1').to('3')));
  EXPECT_TRUE(alex::match("3", alex::from('1').to('3')));
}

TEST(bounds, out_of_bounds)
{
  EXPECT_FALSE(alex::match("0", alex::from('1').to('3')));
  EXPECT_FALSE(alex::match("4", alex::from('1').to('3')));
}

TEST(consumes, consumes_1)
{
  EXPECT_TRUE (alex::match("11", alex::from('1').to('3') + '1' + alex::eof()));
  EXPECT_FALSE(alex::match("1",  alex::from('1').to('3') + '1'));
}

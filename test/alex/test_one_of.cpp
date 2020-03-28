#include "gtest/gtest.h"
#include "alex/alex.h"

template<class T>
auto counted(int* counter, T g)
{
  return alex::grammar([=] (auto& r) {
    (*counter)++;
    return r.match(alex::grammar(g));
  });
}

TEST(basic, single_is_allowed)
{
  EXPECT_TRUE (alex::parser().match("X", alex::one_of('X')));
  EXPECT_FALSE(alex::parser().match("Y", alex::one_of('X')));
}

TEST(chars, matches_either)
{
  EXPECT_TRUE (alex::parser().match("X", alex::one_of('X', 'Y')));
  EXPECT_TRUE (alex::parser().match("Y", alex::one_of('X', 'Y')));
  EXPECT_FALSE(alex::parser().match("?", alex::one_of('X', 'Y')));
}

TEST(chars, consumes_one)
{
  EXPECT_TRUE (alex::parser().match("X",  alex::one_of('X', 'Y')));
  EXPECT_FALSE(alex::parser().match("XY", alex::one_of('X', 'Y')));
}

TEST(strings, matches_either)
{
  EXPECT_TRUE (alex::parser().match("foo", alex::one_of("foo", "bar")));
  EXPECT_TRUE (alex::parser().match("bar", alex::one_of("foo", "bar")));
  EXPECT_FALSE(alex::parser().match("???", alex::one_of("foo", "bar")));
}

TEST(strings, consumes_one)
{
  EXPECT_TRUE (alex::parser().match("foo",    alex::one_of("foo", "bar")));
  EXPECT_FALSE(alex::parser().match("foobar", alex::one_of("foo", "bar")));
}

TEST(order, matches_in_order_of_arguments)
{
  EXPECT_TRUE (alex::parser().match("abc", alex::one_of("abc", "a")));
  EXPECT_FALSE(alex::parser().match("abc", alex::one_of("a", "abc")));
  EXPECT_TRUE (alex::parser().match("abc", alex::one_of("a", "abc") + "bc"));
}

TEST(order, stops_on_match)
{
  int count = 0;
  auto counter = counted(&count, "abc");

  alex::parser().match("abc", alex::one_of("abc", counter));
  EXPECT_EQ(count, 0);

  alex::parser().match("abc", alex::one_of(counter, "abc"));
  EXPECT_EQ(count, 1);
}

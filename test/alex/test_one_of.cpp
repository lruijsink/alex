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
  EXPECT_TRUE (alex::parser().match("X",  alex::one_of('X', 'Y') + alex::eof()));
  EXPECT_FALSE(alex::parser().match("XY", alex::one_of('X', 'Y') + alex::eof()));
}

TEST(strings, matches_either)
{
  EXPECT_TRUE (alex::parser().match("foo", alex::one_of("foo", "bar")));
  EXPECT_TRUE (alex::parser().match("bar", alex::one_of("foo", "bar")));
  EXPECT_FALSE(alex::parser().match("???", alex::one_of("foo", "bar")));
}

TEST(strings, consumes_one)
{
  EXPECT_TRUE (alex::parser().match("foo",    alex::one_of("foo", "bar") + alex::eof()));
  EXPECT_FALSE(alex::parser().match("foobar", alex::one_of("foo", "bar") + alex::eof()));
}

TEST(order, matches_in_order_of_arguments)
{
  EXPECT_TRUE (alex::parser().match("abc", alex::one_of("abc", "a") + alex::eof()));
  EXPECT_FALSE(alex::parser().match("abc", alex::one_of("a", "abc") + alex::eof()));
}

TEST(order, stops_on_match)
{
  int count = 0;
  auto counter = counted(&count, "abc");

  alex::parser().match("abc", alex::one_of(counter, "abc") + alex::eof());
  EXPECT_EQ(count, 1);

  alex::parser().match("abc", alex::one_of("abc", counter) + alex::eof());
  EXPECT_EQ(count, 1);
}

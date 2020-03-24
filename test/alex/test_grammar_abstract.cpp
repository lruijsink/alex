#include <string>

#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/grammar.h"
#include "alex/grammar_abstract.h"
#include "alex/literal.h"

template<class... TS>
auto counted(int* counter, alex::grammar<TS...> g)
{
  return alex::grammar([=] (auto r) {
    (*counter)++;
    return g.match(r);
  });
}

auto true_g = alex::grammar([&] (auto r) {
  return true;
});

auto false_g = alex::grammar([&] (auto r) {
  return false;
});

TEST(delegates, calls_underlying)
{
  auto calls = 0;
  auto poly_true  = alex::grammar<alex::tag::poly>(counted(&calls, true_g));
  auto poly_false = alex::grammar<alex::tag::poly>(counted(&calls, false_g));

  EXPECT_TRUE(alex::parse("abc", poly_true));
  EXPECT_FALSE(alex::parse("abc", poly_false));
  EXPECT_EQ(2, calls);
}

TEST(delegates, copy_calls_underlying)
{
  auto calls = 0;
  auto poly = alex::grammar<alex::tag::poly>(counted(&calls, true_g));
  auto copy = alex::grammar<alex::tag::poly>(poly);

  EXPECT_TRUE(alex::parse("abc", copy));
  EXPECT_EQ(1, calls);
}

TEST(casts, from_char)
{
  EXPECT_TRUE(alex::parse("a", alex::grammar<alex::tag::poly>('a')));
}

TEST(casts, from_const_char)
{
  EXPECT_TRUE(alex::parse("abc", alex::grammar<alex::tag::poly>("abc")));
}

TEST(casts, from_string)
{
  EXPECT_TRUE(alex::parse("xyz", alex::grammar<alex::tag::poly>(std::string("xyz"))));
}

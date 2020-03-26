#include <string>

#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/grammar.h"
#include "alex/literal.h"

#include "alex/grammar_abstract.h"

template<class T>
auto counted(int* counter, T g)
{
  return alex::grammar([=] (auto r) {
    (*counter)++;
    return r.parse(alex::grammar(g));
  });
}

auto true_g = alex::grammar([] (auto r) {
  return true;
});

auto false_g = alex::grammar([] (auto r) {
  return false;
});

TEST(delegates, calls_underlying)
{
  auto calls = 0;
  auto poly_true  = alex::grammar<alex::tag::poly>(counted(&calls, true_g));
  auto poly_false = alex::grammar<alex::tag::poly>(counted(&calls, false_g));

  EXPECT_TRUE(alex::match("abc", poly_true));
  EXPECT_FALSE(alex::match("abc", poly_false));
  EXPECT_EQ(2, calls);
}

TEST(delegates, copy_calls_underlying)
{
  auto calls = 0;
  auto poly = alex::grammar<alex::tag::poly>(counted(&calls, true_g));
  auto copy = alex::grammar<alex::tag::poly>(poly);

  EXPECT_TRUE(alex::match("abc", copy));
  EXPECT_EQ(1, calls);
}

TEST(casts, from_char)
{
  EXPECT_TRUE(alex::match("a", alex::grammar<alex::tag::poly>('a')));
}

TEST(casts, from_const_char)
{
  EXPECT_TRUE(alex::match("abc", alex::grammar<alex::tag::poly>("abc")));
}

TEST(casts, from_string)
{
  EXPECT_TRUE(alex::match("xyz", alex::grammar<alex::tag::poly>(std::string("xyz"))));
}

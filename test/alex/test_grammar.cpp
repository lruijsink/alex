#include "gtest/gtest.h"

#include "alex/any.h"
#include "alex/eof.h"
#include "alex/literal.h"
#include "alex/parse.h"

#include "alex/grammar.h"

auto true_g = alex::grammar([&] (auto r) {
  return true;
});

auto false_g = alex::grammar([&] (auto r) {
  return false;
});

auto not_eof_g = alex::grammar([&] (auto r) {
  return r.get() != std::char_traits<char>::eof();
});

template<class T>
auto counted(int* counter, T g)
{
  return alex::grammar([=] (auto r) {
    (*counter)++;
    return alex::grammar(g).match(r);
  });
}

TEST(delegates, is_called)
{
  auto called = false;
  auto grm = alex::grammar([&] (auto r) {
    called = true;
    return true;
  });

  EXPECT_TRUE(alex::parse("foo", grm));
  EXPECT_TRUE(called);
}

TEST(delegates, compose_and)
{
  EXPECT_FALSE(alex::parse("foo", false_g + false_g));
  EXPECT_FALSE(alex::parse("foo", false_g + true_g));
  EXPECT_FALSE(alex::parse("foo", true_g  + false_g));
  EXPECT_TRUE (alex::parse("foo", true_g  + true_g));
}

TEST(delegates, compose_or)
{
  EXPECT_FALSE(alex::parse("foo", false_g || false_g));
  EXPECT_TRUE (alex::parse("foo", false_g || true_g));
  EXPECT_TRUE (alex::parse("foo", true_g  || false_g));
  EXPECT_TRUE (alex::parse("foo", true_g  || true_g));
}

TEST(delegates, and_invokes_in_order_and_minimal)
{
  int count = 0;

  alex::parse("foo", counted(&count, false_g) + counted(&count, false_g));
  EXPECT_EQ(count, 1);

  alex::parse("foo", counted(&count, false_g) + counted(&count, true_g));
  EXPECT_EQ(count, 2);

  alex::parse("foo", counted(&count, true_g)  + counted(&count, false_g));
  EXPECT_EQ(count, 4);

  alex::parse("foo", counted(&count, true_g)  + counted(&count, true_g));
  EXPECT_EQ(count, 6);
}

TEST(delegates, or_invokes_in_order_and_minimal)
{
  int count = 0;

  alex::parse("foo", counted(&count, false_g) || counted(&count, false_g));
  EXPECT_EQ(count, 2);

  alex::parse("foo", counted(&count, false_g) || counted(&count, true_g));
  EXPECT_EQ(count, 4);

  alex::parse("foo", counted(&count, true_g)  || counted(&count, false_g));
  EXPECT_EQ(count, 5);

  alex::parse("foo", counted(&count, true_g)  || counted(&count, true_g));
  EXPECT_EQ(count, 6);
}

TEST(consume, or_first_does_not_consume)
{
  EXPECT_TRUE (alex::parse("ab", "ab" + alex::eof()));
  EXPECT_TRUE (alex::parse("ab", (false_g || "ab") + alex::eof()));
  EXPECT_FALSE(alex::parse("ab", alex::grammar('x') + alex::eof()));
  EXPECT_TRUE (alex::parse("ab", (alex::grammar('x') || "ab") + alex::eof()));
}

TEST(consume, not_and_first_does_not_consume)
{
  EXPECT_TRUE(alex::parse("ab", "ab" + alex::eof()));
  EXPECT_TRUE(alex::parse("ab", ((false_g + false_g) || "ab") + alex::eof()));
  EXPECT_TRUE(alex::parse("ab", (('a' + false_g) || "ab") + alex::eof()));
}
#include "gtest/gtest.h"
#include "alex/alex.h"

auto true_g = alex::grammar([] (auto& r) {
  return true;
});

auto false_g = alex::grammar([] (auto& r) {
  return false;
});

auto not_eof_g = alex::grammar([] (auto& r) {
  return r.get() != std::char_traits<char>::eof();
});

template<class T>
auto counted(int* counter, T g)
{
  return alex::grammar([=] (auto& r) {
    (*counter)++;
    return r.match(alex::grammar(g));
  });
}

TEST(delegates, is_called)
{
  int count = 0;
  EXPECT_TRUE(alex::parser().match("foo", counted(&count, true_g)));
  EXPECT_EQ(1, count);
}

TEST(delegates, compose_and)
{
  EXPECT_FALSE(alex::parser().match("foo", false_g + false_g));
  EXPECT_FALSE(alex::parser().match("foo", false_g + true_g));
  EXPECT_FALSE(alex::parser().match("foo", true_g  + false_g));
  EXPECT_TRUE (alex::parser().match("foo", true_g  + true_g));
}

TEST(delegates, compose_or)
{
  EXPECT_FALSE(alex::parser().match("foo", false_g || false_g));
  EXPECT_TRUE (alex::parser().match("foo", false_g || true_g));
  EXPECT_TRUE (alex::parser().match("foo", true_g  || false_g));
  EXPECT_TRUE (alex::parser().match("foo", true_g  || true_g));
}

TEST(delegates, and_invokes_in_order_and_minimal)
{
  int count = 0;

  alex::parser().match("foo", counted(&count, false_g) + counted(&count, false_g));
  EXPECT_EQ(count, 1);

  alex::parser().match("foo", counted(&count, false_g) + counted(&count, true_g));
  EXPECT_EQ(count, 2);

  alex::parser().match("foo", counted(&count, true_g)  + counted(&count, false_g));
  EXPECT_EQ(count, 4);

  alex::parser().match("foo", counted(&count, true_g)  + counted(&count, true_g));
  EXPECT_EQ(count, 6);
}

TEST(delegates, or_invokes_in_order_and_minimal)
{
  int count = 0;

  alex::parser().match("foo", counted(&count, false_g) || counted(&count, false_g));
  EXPECT_EQ(count, 2);

  alex::parser().match("foo", counted(&count, false_g) || counted(&count, true_g));
  EXPECT_EQ(count, 4);

  alex::parser().match("foo", counted(&count, true_g)  || counted(&count, false_g));
  EXPECT_EQ(count, 5);

  alex::parser().match("foo", counted(&count, true_g)  || counted(&count, true_g));
  EXPECT_EQ(count, 6);
}

TEST(consume, or_first_does_not_consume)
{
  EXPECT_TRUE (alex::parser().match("ab", "ab" + alex::eof()));
  EXPECT_TRUE (alex::parser().match("ab", (false_g || "ab") + alex::eof()));
  EXPECT_FALSE(alex::parser().match("ab", alex::grammar('x') + alex::eof()));
  EXPECT_TRUE (alex::parser().match("ab", (alex::grammar('x') || "ab") + alex::eof()));
}

TEST(consume, not_and_first_does_not_consume)
{
  EXPECT_TRUE(alex::parser().match("ab", "ab" + alex::eof()));
  EXPECT_TRUE(alex::parser().match("ab", ((false_g + false_g) || "ab") + alex::eof()));
  EXPECT_TRUE(alex::parser().match("ab", (('a' + false_g) || "ab") + alex::eof()));
}

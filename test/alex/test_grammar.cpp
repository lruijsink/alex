#include "gtest/gtest.h"
#include "alex/alex.h"

auto true_g = alex::grammar([] (auto& r) {
  return true;
});

auto false_g = alex::grammar([] (auto& r) {
  return false;
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
  EXPECT_TRUE(alex::parser().match("", counted(&count, true_g)));
  EXPECT_EQ(1, count);
}

TEST(delegates, compose_and)
{
  EXPECT_FALSE(alex::parser().match("", false_g + false_g));
  EXPECT_FALSE(alex::parser().match("", false_g + true_g));
  EXPECT_FALSE(alex::parser().match("", true_g  + false_g));
  EXPECT_TRUE (alex::parser().match("", true_g  + true_g));
}

TEST(delegates, compose_or)
{
  EXPECT_FALSE(alex::parser().match("", false_g || false_g));
  EXPECT_TRUE (alex::parser().match("", false_g || true_g));
  EXPECT_TRUE (alex::parser().match("", true_g  || false_g));
  EXPECT_TRUE (alex::parser().match("", true_g  || true_g));
}

TEST(delegates, and_invokes_in_order_and_minimal)
{
  int count = 0;

  alex::parser().match("", counted(&count, false_g) + counted(&count, false_g));
  EXPECT_EQ(count, 1);

  alex::parser().match("", counted(&count, false_g) + counted(&count, true_g));
  EXPECT_EQ(count, 2);

  alex::parser().match("", counted(&count, true_g)  + counted(&count, false_g));
  EXPECT_EQ(count, 4);

  alex::parser().match("", counted(&count, true_g)  + counted(&count, true_g));
  EXPECT_EQ(count, 6);
}

TEST(delegates, or_invokes_in_order_and_minimal)
{
  int count = 0;

  alex::parser().match("", counted(&count, false_g) || counted(&count, false_g));
  EXPECT_EQ(count, 2);

  alex::parser().match("", counted(&count, false_g) || counted(&count, true_g));
  EXPECT_EQ(count, 4);

  alex::parser().match("", counted(&count, true_g)  || counted(&count, false_g));
  EXPECT_EQ(count, 5);

  alex::parser().match("", counted(&count, true_g)  || counted(&count, true_g));
  EXPECT_EQ(count, 6);
}

TEST(consume, or_first_does_not_consume)
{
  EXPECT_TRUE (alex::parser().match("ab", "ab"));
  EXPECT_TRUE (alex::parser().match("ab", (false_g || "ab")));

  EXPECT_FALSE(alex::parser().match("ab", alex::grammar('x')));
  EXPECT_TRUE (alex::parser().match("ab", (alex::grammar('x') || "ab")));
}

TEST(consume, and_first_does_not_consume)
{
  EXPECT_TRUE(alex::parser().match("ab", "ab"));
  EXPECT_TRUE(alex::parser().match("ab", ((false_g + false_g) || "ab")));
  EXPECT_TRUE(alex::parser().match("ab", (('a' + false_g) || "ab")));
}

#include "gtest/gtest.h"

#include "alex/parse.h"
#include "alex/grammar.h"

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
  auto true_g = alex::grammar([&] (auto r) {
    return true;
  });

  auto false_g = alex::grammar([&] (auto r) {
    return false;
  });

  EXPECT_FALSE(alex::parse("foo", false_g + false_g));
  EXPECT_FALSE(alex::parse("foo", false_g + true_g));
  EXPECT_FALSE(alex::parse("foo", true_g  + false_g));
  EXPECT_TRUE (alex::parse("foo", true_g  + true_g));
}

TEST(delegates, compose_or)
{
  auto true_g = alex::grammar([&] (auto r) {
    return true;
  });

  auto false_g = alex::grammar([&] (auto r) {
    return false;
  });

  EXPECT_FALSE(alex::parse("foo", false_g || false_g));
  EXPECT_TRUE (alex::parse("foo", false_g || true_g));
  EXPECT_TRUE (alex::parse("foo", true_g  || false_g));
  EXPECT_TRUE (alex::parse("foo", true_g  || true_g));
}

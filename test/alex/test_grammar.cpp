#include "gtest/gtest.h"

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

TEST(consumes, consumes_to_end)
{
  EXPECT_TRUE (alex::parse("123", not_eof_g + not_eof_g + not_eof_g));
  EXPECT_FALSE(alex::parse("12",  not_eof_g + not_eof_g + not_eof_g));
}

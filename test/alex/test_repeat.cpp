#include "gtest/gtest.h"

#include "alex/any.h"
#include "alex/eof.h"
#include "alex/from_to.h"
#include "alex/literal.h"
#include "alex/parse.h"

#include "alex/repeat.h"

TEST(defaults, correct_constexprs)
{
  EXPECT_TRUE(alex::repeat('a').has_empty_separator);
  EXPECT_TRUE(alex::repeat('a').has_empty_until);
}

TEST(defaults, match_empty)
{
  auto g = alex::repeat('a') + alex::eof();
  EXPECT_TRUE(alex::match("", g));
}

TEST(defaults, match_pattern)
{
  auto g = alex::repeat('a') + alex::eof();
  EXPECT_TRUE (alex::match("a", g));
  EXPECT_FALSE(alex::match("b", g));
}

TEST(defaults, match_until_eof)
{
  auto g = alex::repeat('a') + alex::eof();
  EXPECT_TRUE(alex::match("aaa", g));
}

TEST(defaults, match_until_mismatch)
{
  auto g = alex::repeat('a') + "bc" + alex::eof();
  EXPECT_TRUE(alex::match("aaabc", g));
}

TEST(defaults, match_string)
{
  auto g = alex::repeat("abc") + alex::eof();
  EXPECT_TRUE (alex::match("abc",    g));
  EXPECT_TRUE (alex::match("abcabc", g));
  EXPECT_FALSE(alex::match("xyz",    g));
}

TEST(defaults, consume_entire_string)
{
  auto g = alex::repeat("aa") + alex::eof();
  EXPECT_TRUE (alex::match("aaaa",  g));
  EXPECT_FALSE(alex::match("aaaaa", g));
}

TEST(min_max, obeys_min)
{
  auto g = alex::repeat("a").min(2) + alex::eof();
  EXPECT_FALSE(alex::match("",     g));
  EXPECT_FALSE(alex::match("a",    g));
  EXPECT_TRUE (alex::match("aa",   g));
  EXPECT_TRUE (alex::match("aaa",  g));
  EXPECT_TRUE (alex::match("aaaa", g));
}

TEST(min_max, obeys_max)
{
  auto g = alex::repeat("a").max(2) + alex::eof();
  EXPECT_TRUE (alex::match("",     g));
  EXPECT_TRUE (alex::match("a",    g));
  EXPECT_TRUE (alex::match("aa",   g));
  EXPECT_FALSE(alex::match("aaa",  g));
  EXPECT_FALSE(alex::match("aaaa", g));
}

TEST(min_max, does_not_stop_at_min)
{
  auto g = alex::repeat("a").min(1) + "a" + alex::eof();
  EXPECT_FALSE(alex::match("aaa", g));
}

TEST(min_max, does_not_have_to_reach_max)
{
  auto g = alex::repeat("a").max(2) + alex::eof();
  EXPECT_TRUE (alex::match("a", g));
}

TEST(min_max, obeys_min_max)
{
  EXPECT_TRUE (alex::match("aaa", alex::repeat("a").min(3).max(3) + alex::eof()));
  EXPECT_TRUE (alex::match("aaa", alex::repeat("a").min(2).max(4) + alex::eof()));
  EXPECT_FALSE(alex::match("aaa", alex::repeat("a").min(2).max(2) + alex::eof()));
  EXPECT_FALSE(alex::match("aaa", alex::repeat("a").min(4).max(4) + alex::eof()));
}

TEST(min_max, no_negative_min)
{
  auto g = alex::repeat("a").min(-1) + alex::eof();
  EXPECT_TRUE(alex::match("", g));
}

TEST(min_max, no_zero_max)
{
  auto g = alex::repeat("a").max(0) + alex::eof();
  EXPECT_TRUE(alex::match("", g));
}

TEST(min_max, min_gt_max_always_mismatch)
{
  auto g1 = alex::repeat("a").min(2).max(1);
  EXPECT_FALSE(alex::match("a",  g1));
  EXPECT_FALSE(alex::match("aa", g1));

  auto g2 = alex::repeat("a").min(2).max(1);
  EXPECT_FALSE(alex::match("a",  g2));
  EXPECT_FALSE(alex::match("aa", g2));
}

TEST(count, matches)
{
  auto g = alex::repeat("a").count(2) + alex::eof();
  EXPECT_FALSE(alex::match("a",   g));
  EXPECT_TRUE (alex::match("aa",  g));
  EXPECT_FALSE(alex::match("aaa", g));
}

TEST(until, matches)
{
  auto g = alex::repeat('a').until('b') + alex::eof();
  EXPECT_TRUE (alex::match("aab", g));
  EXPECT_FALSE(alex::match("aaX", g));
}

TEST(until, must_end_on_terminator)
{
  auto g = alex::repeat('a').until('b') + alex::eof();
  EXPECT_TRUE (alex::match("aab", g));
  EXPECT_FALSE(alex::match("aXb", g));
}

TEST(until, consumes_terminator)
{
  auto g = alex::repeat('a').until('b') + alex::eof();
  EXPECT_TRUE (alex::match("aab", g));
}

TEST(until, consumes_terminator_once)
{
  auto g = alex::repeat('a').until('b') + alex::eof();
  EXPECT_FALSE(alex::match("aabb", g));
}

TEST(until, with_min)
{
  auto g = alex::repeat('a').until('b').min(2) + alex::eof();
  EXPECT_FALSE(alex::match("b",      g));
  EXPECT_FALSE(alex::match("ab",     g));
  EXPECT_TRUE (alex::match("aab",    g));
  EXPECT_TRUE (alex::match("aaab",   g));
  EXPECT_TRUE (alex::match("aaaab",  g));
}

TEST(until, with_max)
{
  auto g = alex::repeat('a').until('b').max(2) + alex::eof();
  EXPECT_TRUE (alex::match("b",     g));
  EXPECT_TRUE (alex::match("ab",    g));
  EXPECT_TRUE (alex::match("aab",   g));
  EXPECT_FALSE(alex::match("aaab",  g));
  EXPECT_FALSE(alex::match("aaaab", g));
}

TEST(until, with_min_max)
{
  auto g = alex::repeat('a').until('b').min(1).max(3) + alex::eof();
  EXPECT_FALSE(alex::match("b",     g));
  EXPECT_TRUE (alex::match("ab",    g));
  EXPECT_TRUE (alex::match("aab",   g));;
  EXPECT_TRUE (alex::match("aaab",  g));
  EXPECT_FALSE(alex::match("aaaab", g));
}

TEST(until, with_min_gt_max)
{
  auto g = alex::repeat('a').until('b').min(2).max(1);
  EXPECT_FALSE(alex::match("b",   g));
  EXPECT_FALSE(alex::match("ab",  g));
  EXPECT_FALSE(alex::match("aab", g));
}

TEST(until, with_count)
{
  auto g = alex::repeat('a').until('b').count(1) + alex::eof();
  EXPECT_FALSE(alex::match("b",   g));
  EXPECT_TRUE (alex::match("ab",  g));
  EXPECT_FALSE(alex::match("aab", g));
}

TEST(until, with_strings)
{
  auto g = alex::repeat("aa").until("bb") + alex::eof();
  EXPECT_TRUE (alex::match("bb",     g));
  EXPECT_FALSE(alex::match("abb",    g));
  EXPECT_TRUE (alex::match("aabb",   g));
  EXPECT_FALSE(alex::match("aaabb",  g));
  EXPECT_TRUE (alex::match("aaaabb", g));
}

TEST(separator, single)
{
  auto g = alex::repeat('a').separator(',') + alex::eof();
  EXPECT_TRUE (alex::match("a",  g));
  EXPECT_FALSE(alex::match("a,", g));
}

TEST(separator, requires_separator)
{
  auto g = alex::repeat('a').separator(',') + alex::eof();
  EXPECT_TRUE (alex::match("a,a,a", g));
  EXPECT_FALSE(alex::match("aaa",   g));
}

TEST(separator, with_strings)
{
  auto g = alex::repeat("ab").separator("..") + alex::eof();
  EXPECT_TRUE (alex::match("ab..ab", g));
  EXPECT_FALSE(alex::match("ab.ab",  g));
  EXPECT_FALSE(alex::match("a..b",   g));
}

TEST(separator, may_not_start_with_separator)
{
  auto g = alex::repeat('a').separator(',') + alex::eof();
  EXPECT_TRUE (alex::match("a,a,a",  g));
  EXPECT_FALSE(alex::match(",a,a,a", g));
}

TEST(separator, may_not_end_on_separator)
{
  auto g = alex::repeat('a').separator(',') + alex::eof();
  EXPECT_TRUE (alex::match("a,a,a", g));
  EXPECT_FALSE(alex::match("a,a,",  g));
}

TEST(separator, only_one_separator)
{
  auto g = alex::repeat('a').separator(',') + alex::eof();
  EXPECT_TRUE (alex::match("a,a,a",   g));
  EXPECT_FALSE(alex::match("a,,a,,a", g));
}

TEST(separator, with_min)
{
  auto g = alex::repeat('a').separator(',').min(2) + alex::eof();
  EXPECT_FALSE(alex::match("",      g));
  EXPECT_FALSE(alex::match("a",     g));
  EXPECT_TRUE (alex::match("a,a",   g));
  EXPECT_TRUE (alex::match("a,a,a", g));
}

TEST(separator, with_max)
{
  auto g = alex::repeat('a').separator(',').max(1) + alex::eof();
  EXPECT_TRUE (alex::match("",      g));
  EXPECT_TRUE (alex::match("a",     g));
  EXPECT_FALSE(alex::match("a,a",   g));
  EXPECT_FALSE(alex::match("a,a,a", g));
}

TEST(separator, with_min_max)
{
  auto g = alex::repeat('a').separator(',').min(1).max(3) + alex::eof();
  EXPECT_FALSE(alex::match("",        g));
  EXPECT_TRUE (alex::match("a",       g));
  EXPECT_TRUE (alex::match("a,a",     g));
  EXPECT_TRUE (alex::match("a,a,a",   g));
  EXPECT_FALSE(alex::match("a,a,a,a", g));
}

TEST(separator, with_min_gt_max)
{
  auto g = alex::repeat('a').separator(',').min(2).max(1) + alex::eof();
  EXPECT_FALSE(alex::match("",      g));
  EXPECT_FALSE(alex::match("a",     g));
  EXPECT_FALSE(alex::match("a,a",   g));
  EXPECT_FALSE(alex::match("a,a,a", g));
}

TEST(separator, with_count)
{
  auto g = alex::repeat('a').separator(',').count(2) + alex::eof();
  EXPECT_FALSE(alex::match("a",     g));
  EXPECT_TRUE (alex::match("a,a",   g));
  EXPECT_FALSE(alex::match("a,a,a", g));
}

TEST(combined, floating_point)
{
  auto num = alex::from('0').to('9');
  auto g = alex::repeat(num).until('.').min(1) + alex::repeat(num).min(1);

  EXPECT_FALSE(alex::match(".0",      g + alex::eof()));
  EXPECT_FALSE(alex::match("123.",    g + alex::eof()));
  EXPECT_TRUE (alex::match("0.0",     g + alex::eof()));
  EXPECT_TRUE (alex::match("123.456", g + alex::eof()));
}

TEST(combined, string_escaping)
{
  auto escaped_char = '\\' + alex::any();
  auto str_char = escaped_char || alex::any();
  auto str_content = alex::repeat(str_char);
  auto str = "'" + str_content.until("'");

  EXPECT_TRUE (alex::match("ab", str_char + str_char));
  EXPECT_TRUE (alex::match("ab", str_content));
  EXPECT_FALSE(alex::match("ab", escaped_char));
  EXPECT_FALSE(alex::match("ab", str_char + alex::eof()));
  EXPECT_TRUE (alex::match("ab", str_char + 'b' + alex::eof()));

  EXPECT_TRUE (alex::match("''",         str + alex::eof()));
  EXPECT_TRUE (alex::match("'abcd'",     str + alex::eof()));
  EXPECT_FALSE(alex::match("'ab'cd'",    str + alex::eof()));
  EXPECT_TRUE (alex::match("'ab\\'cd'",  str + alex::eof()));
  EXPECT_TRUE (alex::match("'ab\\cd'",   str + alex::eof()));
  EXPECT_TRUE (alex::match("'ab\\\\cd'", str + alex::eof()));
  EXPECT_FALSE(alex::match("'abcd\\'",   str + alex::eof()));
  EXPECT_TRUE (alex::match("'abcd\\\\'", str + alex::eof()));
}

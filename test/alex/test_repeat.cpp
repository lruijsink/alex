#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(defaults, match_empty)
{
  auto g = alex::repeat('a') + alex::eof();
  EXPECT_TRUE(alex::parser().match("", g));
}

TEST(defaults, match_pattern)
{
  auto g = alex::repeat('a') + alex::eof();
  EXPECT_TRUE (alex::parser().match("a", g));
  EXPECT_FALSE(alex::parser().match("b", g));
}

TEST(defaults, match_until_eof)
{
  auto g = alex::repeat('a') + alex::eof();
  EXPECT_TRUE(alex::parser().match("aaa", g));
}

TEST(defaults, match_until_mismatch)
{
  auto g = alex::repeat('a') + "bc" + alex::eof();
  EXPECT_TRUE(alex::parser().match("aaabc", g));
}

TEST(defaults, match_string)
{
  auto g = alex::repeat("abc") + alex::eof();
  EXPECT_TRUE (alex::parser().match("abc",    g));
  EXPECT_TRUE (alex::parser().match("abcabc", g));
  EXPECT_FALSE(alex::parser().match("xyz",    g));
}

TEST(defaults, consume_entire_string)
{
  auto g = alex::repeat("aa") + alex::eof();
  EXPECT_TRUE (alex::parser().match("aaaa",  g));
  EXPECT_FALSE(alex::parser().match("aaaaa", g));
}

TEST(separator, single)
{
  auto g = alex::repeat('a', ',') + alex::eof();
  EXPECT_TRUE (alex::parser().match("a",  g));
  EXPECT_FALSE(alex::parser().match("a,", g));
}

TEST(separator, requires_separator)
{
  auto g = alex::repeat('a', ',') + alex::eof();
  EXPECT_TRUE (alex::parser().match("a,a,a", g));
  EXPECT_FALSE(alex::parser().match("aaa",   g));
}

TEST(separator, with_strings)
{
  auto g = alex::repeat("ab", "..") + alex::eof();
  EXPECT_TRUE (alex::parser().match("ab..ab", g));
  EXPECT_FALSE(alex::parser().match("ab.ab",  g));
  EXPECT_FALSE(alex::parser().match("a..b",   g));
}

TEST(separator, may_not_start_with_separator)
{
  auto g = alex::repeat('a', ',') + alex::eof();
  EXPECT_TRUE (alex::parser().match("a,a,a",  g));
  EXPECT_FALSE(alex::parser().match(",a,a,a", g));
}

TEST(separator, may_not_end_on_separator)
{
  auto g = alex::repeat('a', ',') + alex::eof();
  EXPECT_TRUE (alex::parser().match("a,a,a", g));
  EXPECT_FALSE(alex::parser().match("a,a,",  g));
}

TEST(separator, only_one_separator)
{
  auto g = alex::repeat('a', ',') + alex::eof();
  EXPECT_TRUE (alex::parser().match("a,a,a",   g));
  EXPECT_FALSE(alex::parser().match("a,,a,,a", g));
}

TEST(combined, floating_point)
{
  auto num = alex::from_to('0', '9');
  auto min1 = num + alex::repeat(num);
  auto g = min1 + '.' + min1;

  EXPECT_FALSE(alex::parser().match(".0",      g + alex::eof()));
  EXPECT_FALSE(alex::parser().match("123.",    g + alex::eof()));
  EXPECT_TRUE (alex::parser().match("0.0",     g + alex::eof()));
  EXPECT_TRUE (alex::parser().match("123.456", g + alex::eof()));
}

TEST(combined, string_escaping)
{
  auto delim = '\'';
  auto escaped_char = '\\' + alex::any();
  auto str_char = escaped_char || alex::any_but(delim);
  auto str_content = alex::repeat(str_char);
  auto str = delim + str_content + delim;

  EXPECT_TRUE (alex::parser().match("ab", str_char + str_char));
  EXPECT_TRUE (alex::parser().match("ab", str_content));
  EXPECT_FALSE(alex::parser().match("ab", escaped_char));
  EXPECT_FALSE(alex::parser().match("ab", str_char + alex::eof()));
  EXPECT_TRUE (alex::parser().match("ab", str_char + 'b' + alex::eof()));

  EXPECT_TRUE (alex::parser().match("''",         str + alex::eof()));
  EXPECT_TRUE (alex::parser().match("'abcd'",     str + alex::eof()));
  EXPECT_FALSE(alex::parser().match("'ab'cd'",    str + alex::eof()));
  EXPECT_TRUE (alex::parser().match("'ab\\'cd'",  str + alex::eof()));
  EXPECT_TRUE (alex::parser().match("'ab\\cd'",   str + alex::eof()));
  EXPECT_TRUE (alex::parser().match("'ab\\\\cd'", str + alex::eof()));
  EXPECT_FALSE(alex::parser().match("'abcd\\'",   str + alex::eof()));
  EXPECT_TRUE (alex::parser().match("'abcd\\\\'", str + alex::eof()));
}

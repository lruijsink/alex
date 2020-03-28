#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(defaults, match_empty)
{
  EXPECT_TRUE(alex::parser().match("", alex::repeat('a')));
}

TEST(defaults, match_pattern)
{
  EXPECT_TRUE (alex::parser().match("a", alex::repeat('a')));
  EXPECT_FALSE(alex::parser().match("b", alex::repeat('a')));
}

TEST(defaults, match_until_eof)
{
  EXPECT_TRUE(alex::parser().match("aaa", alex::repeat('a')));
}

TEST(defaults, match_until_mismatch)
{
  EXPECT_TRUE(alex::parser().match("aaabc", alex::repeat('a') + "bc"));
}

TEST(defaults, match_string)
{
  EXPECT_TRUE (alex::parser().match("abc",    alex::repeat("abc")));
  EXPECT_TRUE (alex::parser().match("abcabc", alex::repeat("abc")));
  EXPECT_FALSE(alex::parser().match("xyz",    alex::repeat("abc")));
}

TEST(defaults, consumes_whole_pattern)
{
  EXPECT_TRUE (alex::parser().match("aaaa",  alex::repeat("aa")));
  EXPECT_FALSE(alex::parser().match("aaaaa", alex::repeat("aa")));
}

TEST(separator, single)
{
  EXPECT_TRUE (alex::parser().match("a",  alex::repeat('a', ',')));
  EXPECT_FALSE(alex::parser().match("a,", alex::repeat('a', ',')));
}

TEST(separator, requires_separator)
{
  EXPECT_TRUE (alex::parser().match("a,a,a", alex::repeat('a', ',')));
  EXPECT_FALSE(alex::parser().match("aaa",   alex::repeat('a', ',')));
}

TEST(separator, may_not_start_with_separator)
{
  EXPECT_TRUE (alex::parser().match("a,a,a",  alex::repeat("a", ',')));
  EXPECT_FALSE(alex::parser().match(",a,a,a", alex::repeat("a", ',')));
}

TEST(separator, may_not_end_on_separator)
{
  EXPECT_TRUE (alex::parser().match("a,a,a", alex::repeat('a', ',')));
  EXPECT_FALSE(alex::parser().match("a,a,",  alex::repeat('a', ',')));
}

TEST(separator, only_one_separator)
{
  EXPECT_TRUE (alex::parser().match("a,a,a",   alex::repeat('a', ',')));
  EXPECT_FALSE(alex::parser().match("a,,a,,a", alex::repeat('a', ',')));
}

TEST(separator, with_strings)
{
  EXPECT_TRUE (alex::parser().match("ab..ab", alex::repeat("ab", "..")));
  EXPECT_FALSE(alex::parser().match("ab.ab",  alex::repeat("ab", "..")));
  EXPECT_FALSE(alex::parser().match("a..b",   alex::repeat("ab", "..")));
}

TEST(combined, floating_point)
{
  auto num = alex::from_to('0', '9');
  auto min1 = num + alex::repeat(num);
  auto g = min1 + '.' + min1;

  EXPECT_FALSE(alex::parser().match(".0",      g));
  EXPECT_FALSE(alex::parser().match("123.",    g));
  EXPECT_TRUE (alex::parser().match("0.0",     g));
  EXPECT_TRUE (alex::parser().match("123.456", g));
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
  EXPECT_FALSE(alex::parser().match("ab", str_char));
  EXPECT_TRUE (alex::parser().match("ab", str_char + 'b'));

  EXPECT_TRUE (alex::parser().match("''",         str));
  EXPECT_TRUE (alex::parser().match("'abcd'",     str));
  EXPECT_FALSE(alex::parser().match("'ab'cd'",    str));
  EXPECT_TRUE (alex::parser().match("'ab\\'cd'",  str));
  EXPECT_TRUE (alex::parser().match("'ab\\cd'",   str));
  EXPECT_TRUE (alex::parser().match("'ab\\\\cd'", str));
  EXPECT_FALSE(alex::parser().match("'abcd\\'",   str));
  EXPECT_TRUE (alex::parser().match("'abcd\\\\'", str));
}

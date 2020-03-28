#include "gtest/gtest.h"
#include "alex/alex.h"

TEST(explicit_construct, match_char)
{
  EXPECT_TRUE (alex::parser().match("a", alex::grammar<char>('a')));
  EXPECT_FALSE(alex::parser().match("z", alex::grammar<char>('a')));
}

TEST(explicit_construct, match_const_char)
{
  EXPECT_TRUE (alex::parser().match("abc", alex::grammar<const char*>("abc")));
  EXPECT_FALSE(alex::parser().match("xyz", alex::grammar<const char*>("abc")));
}

TEST(explicit_construct, match_string)
{
  EXPECT_TRUE (alex::parser().match("abc", alex::grammar<std::string>(std::string("abc"))));
  EXPECT_FALSE(alex::parser().match("xyz", alex::grammar<std::string>(std::string("abc"))));
}

TEST(implicit_cast, match_char)
{
  EXPECT_TRUE (alex::parser().match("a", alex::grammar('a')));
  EXPECT_FALSE(alex::parser().match("z", alex::grammar('a')));
}

TEST(implicit_cast, match_const_char)
{
  EXPECT_TRUE (alex::parser().match("abc", alex::grammar("abc")));
  EXPECT_FALSE(alex::parser().match("xyz", alex::grammar("abc")));
}

TEST(implicit_cast, match_string)
{
  EXPECT_TRUE (alex::parser().match("abc", alex::grammar(std::string("abc"))));
  EXPECT_FALSE(alex::parser().match("xyz", alex::grammar(std::string("abc"))));
}

TEST(consumes, consumes_char)
{
  EXPECT_TRUE (alex::parser().match("12", alex::grammar('1') + alex::grammar('2')));
  EXPECT_FALSE(alex::parser().match("X",  alex::grammar('X') + alex::grammar('X')));
}

TEST(consumes, consumes_const_char)
{
  EXPECT_TRUE (alex::parser().match("123456", alex::grammar("123") + alex::grammar("456")));
  EXPECT_FALSE(alex::parser().match("12345",  alex::grammar("123") + alex::grammar("456")));
}

TEST(consumes, consumes_string)
{
  EXPECT_TRUE (alex::parser().match("123456", alex::grammar(std::string("123")) + alex::grammar(std::string("456"))));
  EXPECT_FALSE(alex::parser().match("12345",  alex::grammar(std::string("123")) + alex::grammar(std::string("456"))));
}

TEST(composes, compose_char)
{
  EXPECT_TRUE (alex::parser().match("123", alex::any() + '2' + '3'));
  EXPECT_FALSE(alex::parser().match("abc", alex::any() + '2' + '3'));
  EXPECT_TRUE (alex::parser().match("123", '1' + alex::any() + alex::any()));
  EXPECT_FALSE(alex::parser().match("abc", '1' + alex::any() + alex::any()));
}

TEST(composes, compose_const_char)
{
  EXPECT_TRUE (alex::parser().match("12345", alex::any() + "23" + "45"));
  EXPECT_FALSE(alex::parser().match("abcde", alex::any() + "23" + "45"));
  EXPECT_TRUE (alex::parser().match("12345", "123" + alex::any() + alex::any()));
  EXPECT_FALSE(alex::parser().match("abcde", "123" + alex::any() + alex::any()));
}

TEST(composes, compose_string)
{
  EXPECT_TRUE (alex::parser().match("12345", alex::any() + std::string("23") + std::string("45")));
  EXPECT_FALSE(alex::parser().match("abcde", alex::any() + std::string("23") + std::string("45")));
  EXPECT_TRUE (alex::parser().match("12345", std::string("12") + std::string("34") + alex::any()));
  EXPECT_FALSE(alex::parser().match("abcde", std::string("12") + std::string("34") + alex::any()));
}

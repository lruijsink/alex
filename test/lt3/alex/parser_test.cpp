#include <string_view>
#include "gtest/gtest.h"
#include "lt3/alex.h"

TEST(stream_range_test, stream_get)
{
  auto source = std::string_view("1234");
  auto parser = lt3::alex::parser(source);

  EXPECT_EQ(parser.stream().get(), '1');
  EXPECT_EQ(parser.stream().get(), '2');
  EXPECT_EQ(parser.stream().get(), '3');
  EXPECT_EQ(parser.stream().get(), '4');
  EXPECT_TRUE(parser.stream().eof());
}

TEST(stream_range_test, repeat)
{
  auto source = std::string_view("1112");
  auto parser = lt3::alex::parser(source);

  EXPECT_TRUE(parser.parse(lt3::alex::repeat('1')));
  EXPECT_TRUE(parser.parse('2'));
  EXPECT_TRUE(parser.stream().eof());
}

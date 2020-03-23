#include <string_view>
#include "gtest/gtest.h"
#include "lt3/alex.h"

TEST(stream_range_test, stream_get)
{
  auto source = std::string_view("1234");
  auto parser = lt3::alex::parser(source);
}

TEST(stream_range_test, repeat)
{
  auto source = std::string_view("1112");
  auto parser = lt3::alex::parser(source);
}

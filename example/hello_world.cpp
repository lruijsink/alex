#include <string_view>
#include <type_traits>
#include <iostream>
#include "lt3/alex.h"

using namespace lt3;

int main()
{
  auto source = std::string_view("Hello world!");
  auto parser = alex::parser(source);

  auto res1 = parser.parse(alex::character('h')); // false
  auto res2 = parser.parse(alex::character('H')); // true
}

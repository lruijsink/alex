#include <string_view>
#include <iostream>
#include "lt3/alex.h"

using namespace lt3;

int main()
{
  auto letter = alex::from_to('a', 'z') || alex::from_to('A', 'Z');
  auto digit  = alex::from_to('0', '9');
  auto uscore = alex::character('_');

  auto identifier = (letter || uscore)
                  + alex::repeat(letter || uscore || digit);

  auto good = std::string_view("a_proper_identifier");
  auto bad  = std::string_view("1_bad_identifier");

  std::cout << alex::parser(good).parse(identifier) << "\n"; // true
  std::cout << alex::parser(bad) .parse(identifier) << "\n"; // false
}

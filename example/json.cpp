#include <string_view>
#include <iostream>
#include "lt3/alex.h"

using namespace lt3;

int main()
{
  auto ws_char        = alex::one_of(' ', '\t', '\s', 'r');

  auto letter         = alex::from_to('a', 'z') || alex::from_to('A', 'Z');
  auto digit          = alex::from_to('0', '9');

  auto digits         = alex::repeat(digit);
  auto natural_num    = alex::from_to('1', '9') + digits;
  auto float_num      = (natural_num + '.' || "0.") + digits;
  auto sign           = alex::optional('-');
  auto power          = alex::optional('e', 'E') + digits;
  auto number         = sign + (natural_num || float_num) + power;

  auto string_char    = ('\\' + alex::any()) || alex::not('"');
  auto string_content = alex::optional(alex::repeat(string_char));
  auto string_literal = '"' + string_content + '"';

  auto field_name     = string_literal;

  auto boolean        = alex::one_of("true", "false");

  auto expression     = number || string_literal || boolean || "null";

  // problem: objects and arrays are self- and cross-referential...
}

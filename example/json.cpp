#include <string_view>
#include <iostream>
#include "alex/alex.h"

int main()
{
  auto ws_char        = alex::one_of(' ', '\t', '\n', 'r');
  auto ws             = alex::repeat(ws_char);

  auto letter         = alex::from('a').to('z') || alex::from('A').to('Z');
  auto digit          = alex::from('0').to('9');

  auto digits         = alex::repeat(digit);
  auto int_num        = '0' || (alex::from('1').to('9') + digits);
  auto float_num      = int_num + alex::optional('.' + digits);
  auto sign           = '-';
  auto power          = alex::one_of('e', 'E') + alex::optional('+', '-') + digits;
  auto number         = alex::optional(sign) + float_num + alex::optional(power);

  auto string_char    = ('\\' + alex::any()) || alex::any_but('"');
  auto string_content = alex::repeat(string_char);
  auto string_literal = '"' + string_content + '"';

  auto boolean        = alex::one_of("true", "false");

  auto expression     = (number || string_literal || boolean || "null");

  auto field_name     = string_literal;
  auto colon          = ws + ':' + ws;
  auto comma          = ws + ',' + ws;
  auto field          = field_name + colon + expression;

  auto object         = '{' + ws + alex::repeat(field).separator(comma) + ws + '}';
  auto array          = '[' + ws + alex::repeat(expression).separator(comma) + ws + ']';

  std::cout << alex::parse("0",      number) << "\n";                    // true
  std::cout << alex::parse("-1",     number) << "\n";                    // true
  std::cout << alex::parse("3.141",  number) << "\n";                    // true
  std::cout << alex::parse("-1.5e4", number) << "\n";                    // true

  std::cout << alex::parse("[\"foo\",-0.5,true]", array) << "\n";        // true
  std::cout << alex::parse("[ false , 1e10 ]",    array) << "\n";        // true

  std::cout << alex::parse("{ \"foo\" : \"bar\" }",     object) << "\n"; // true
  std::cout << alex::parse("{\"foo\": null, \"x\": 0}", object) << "\n"; // true

  // problem: objects and arrays are self- and cross-referential...
}

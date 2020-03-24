#include <iostream>
#include "alex/alex.h"

using namespace alex;

int main()
{
  auto ws             = repeat(one_of(' ', '\t', '\n', 'r'));

  auto letter         = from('a').to('z') || from('A').to('Z');
  auto digit          = from('0').to('9');

  auto digits         = repeat(digit);
  auto int_num        = '0' || (from('1').to('9') + digits);
  auto float_num      = int_num + optional('.' + digits);
  auto sign           = '-';
  auto power          = one_of('e', 'E') + optional('+', '-') + digits;
  auto number         = optional(sign) + float_num + optional(power);

  auto string_literal = '"' + repeat(('\\' + any()) || any_but('"')).until('"');

  auto keyword        = one_of("true", "false", "null");

  auto object         = recursive();
  auto array          = recursive();

  auto expression     = (object || array || number || string_literal || keyword);

  auto comma          = ws + ',' + ws;
       array          = '[' + ws + repeat(expression).separator(comma) + ws + ']';

  auto colon          = ws + ':' + ws;
  auto field          = string_literal + colon + expression;
       object         = '{' + ws + repeat(field).separator(comma) + ws + '}';

  auto json           = ws + expression + ws;

  std::cout << parse("0",      json) << "\n";                        // true
  std::cout << parse("-1",     json) << "\n";                        // true
  std::cout << parse("3.141",  json) << "\n";                        // true
  std::cout << parse("-1.5e4", json) << "\n";                        // true
                                                                       
  std::cout << parse("[\"foo\",-0.5,true]", json) << "\n";           // true
  std::cout << parse("[ false , 1e10 ]",    json) << "\n";           // true
                                                                       
  std::cout << parse("{ \"foo\" : \"bar\" }",     json) << "\n";     // true
  std::cout << parse("{\"foo\": null, \"x\": 0}", json) << "\n";     // true

  std::cout << parse("{\"outer\" : {\"inner\" : 0}}", json) << "\n"; // true

  std::cout << parse("[\"outer\", [\"inner\"]]", json) << "\n";      // true
}

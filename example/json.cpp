#include <iostream>
#include "alex/alex.h"

using namespace alex;

int main()
{
  auto ws             = repeat(one_of(' ', '\t', '\n', 'r'));

  auto digits         = repeat(from('0').to('9'));
  auto int_num        = '0' || (from('1').to('9') + digits);
  auto float_num      = int_num + optional('.' + digits);
  auto power          = one_of('e', 'E') + optional('+', '-') + digits;
  auto number         = optional('-') + float_num + optional(power);

  auto string_literal = '"' + repeat(('\\' + any()) || any_but('"')).until('"');

  auto keyword        = one_of("true", "false", "null");

  auto object         = recursive();
  auto array          = recursive();

  auto expression     = (object || array || number || string_literal || keyword);

  auto field          = string_literal + ws + ':' + ws + expression;
       object         = '{' + ws + repeat(field).separator(ws + ',' + ws) + ws + '}';

       array          = '[' + ws + repeat(expression).separator(ws + ',' + ws) + ws + ']';

  auto json           = ws + expression + ws;

  std::cout << match("0",      json) << "\n";                        // true
  std::cout << match("-1",     json) << "\n";                        // true
  std::cout << match("3.141",  json) << "\n";                        // true
  std::cout << match("-1.5e4", json) << "\n";                        // true
                                                                       
  std::cout << match("[\"foo\",-0.5,true]", json) << "\n";           // true
  std::cout << match("[ false , 1e10 ]",    json) << "\n";           // true
                                                                       
  std::cout << match("{ \"foo\" : \"bar\" }",     json) << "\n";     // true
  std::cout << match("{\"foo\": null, \"x\": 0}", json) << "\n";     // true

  std::cout << match("{\"outer\" : {\"inner\" : 0}}", json) << "\n"; // true

  std::cout << match("[\"outer\", [\"inner\"]]", json) << "\n";      // true
}

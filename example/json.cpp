#include <iostream>
#include "alex/alex.h"

using namespace alex;

void print_tree(symbol_tree st, int idx = 0)
{
  for (int i = 0; i < idx; i++)
    std::cout << "- ";
  std::cout << st.name();
  std::cout << "\n";
  for (auto& lf : st.leaves())
    print_tree(lf, idx + 1);
}

int main()
{
  auto ws          = repeat(one_of(' ', '\t', '\n', 'r'));
  auto digits      = repeat(from_to('0', '9'));
  auto int_num     = '0' || (from_to('1', '9') + digits);
  auto float_num   = int_num + optional('.' + digits);
  auto power       = one_of('e', 'E') + optional('+', '-') + digits;
                   
  auto object      = recursive();
  auto array       = recursive();

  auto number      = symbol("number",      optional('-') + float_num + optional(power));
  auto text        = symbol("text",        '"' + repeat(('\\' + any()) || any_but('"')).until('"'));
  auto keyword     = symbol("boolean",     one_of("true", "false")) || symbol("null", "null");
  auto expression  = symbol("expression",  object || array || number || text || keyword);
  auto field_name  = symbol("field_name",  text);
  auto field_value = symbol("field_value", expression);
  auto field       = symbol("field",       field_name + ws + ':' + ws + field_value);
       object      = symbol("object",      '{' + ws + repeat(field).separator(ws + ',' + ws) + ws + '}');
       array       = symbol("array",       '[' + ws + repeat(expression).separator(ws + ',' + ws) + ws + ']');

  auto json        = ws + expression + ws;

  print_tree(parse("{\"foo\": \"bar\", \"fi\":[\"ga\", [\"r\", 0.0]]}", json));
}

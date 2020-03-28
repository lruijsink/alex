#include <iostream>
#include "alex/alex.h"

using namespace alex;

void print_tree(symbol_tree st, int idx = 0)
{
  for (int i = 0; i < idx; i++)
    std::cout << "- ";
  std::cout << st.name() << std::string(16 - st.name().length(), ' ') << st.content() << "\n";
  for (auto& lf : st.leaves())
    print_tree(lf, idx + 1);
}

int main()
{
  auto ws          = repeat(one_of(' ', '\t', '\n', 'r'));
  auto op          = [=] (auto g) { return ws + g + ws; };

  auto digits      = repeat(from_to('0', '9'));
  auto int_num     = '0' || (from_to('1', '9') + digits);
  auto float_num   = int_num + optional('.' + digits);
  auto power       = one_of('e', 'E') + optional('+', '-') + digits;
                   
  auto object      = recursive();
  auto array       = recursive();

  auto boolean     = symbol("boolean", one_of("true", "false"));
  auto null        = symbol("null",    "null");
  auto keyword     = boolean || null;

  auto number      = symbol("number", optional('-') + float_num + optional(power));
  auto text        = symbol("text",   '"' + repeat(('\\' + any()) || any_but('"')) + '"');
  
  auto expression  = object || array || number || text || keyword;
  
  auto field       = symbol("field",  text + op(':') + expression);
       object      = symbol("object", op('{') + repeat(field).separator(op(',')) + op('}'));
       array       = symbol("array",  op('[') + repeat(expression).separator(op(',')) + op(']'));

  auto json        = expression;

  print_tree(parse("{\"foo\": \"bar\", \"fi\":[\"ga\", [\"r\", 0.0]]}", json));
}

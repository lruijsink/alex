#include "alex.h"
using namespace alex;

constexpr parsing_result expression(parsing_iterator itr, parsing_context& context);

constexpr auto ws = repeat(choice(' ', '\t', '\r', '\n'));
constexpr auto op = [] (auto l) { return ws + l + ws; };

constexpr auto number_v
= optional('-')
+ ('0' | (char_range('1', '9') + repeat(char_range('0', '9'))))
+ optional
  ('.' + repeat_min_1(char_range('0', '9')))
+ optional
  (choice('e', 'E') + optional(choice('-', '+')) + repeat_min_1(char_range('0', '9')));

constexpr auto string_v
= '"' + repeat(('\\' + any_char) | any_char_but('"')) + '"';

constexpr auto keyword_v
= choice("null", "true", "false");

constexpr auto array_v
= '[' + repeat_separated(expression, op(',')) + ']';

constexpr auto object_v
= '{' + repeat_separated(ws + string_v + ws + ':' + expression, ',') + '}';

constexpr parsing_result expression(parsing_iterator itr, parsing_context& context) {
  return (ws + ( object_v | array_v | string_v | number_v | keyword_v) + ws) (itr, context);
}

int main() {
  constexpr auto json = expression;
}

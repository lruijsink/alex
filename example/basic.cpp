#include <iostream>
#include <vector>
#include "alex/alex.hpp"

using namespace alex;

namespace alex {

class tokenizer {
  using token_type = std::string_view;
  using index_type = size_t;
  static constexpr index_type root = 999999;
  struct node {
    token_type token;
    index_type parent;
    std::string_view text;
  };

  std::vector<node> stack_{};
  index_type parent_ = root;

 public:
  constexpr auto operator()(token_type token, Lexifiable auto expr) {
    auto lex = lexify(expr);
    return [=, this](std::string_view text) {
      auto parent = parent_;
      auto me = stack_.size();
      parent_ = me;
      stack_.push_back({token, parent});

      auto res = lex(text);
      if (res) {
        stack_[me].text = text.substr(0, *res);
      } else {
        stack_.erase(stack_.begin() + me, stack_.end());
      }
      parent_ = parent;
      return res;
    };
  }

  index_type print(index_type me, int d) {
    auto [token, parent, text] = stack_[me];

    for (int i = 0; i < d; i++) std::cout << "  ";
    std::cout << token << ": " << text << '\n';

    auto it = me + 1;
    while (it < stack_.size() && stack_[it].parent == me) {
      it = print(it, d + 1);
    }

    return it;
  }

  void print() { print(0, 0); }
};

}  // namespace alex

auto cf(std::string_view text) {
  auto token = tokenizer();
  auto whitespace = repeat(choice(' ', '\r', '\n', '\t'));
  auto op = [=](char c) { return whitespace + c + whitespace; };

  recursive expr;
  auto digit = range('0', '9');
  auto number = token("number", ('0' | range('1', '9') + repeat(digit)));
  auto string = token("string", '"' + repeat('\\' + any | noneOf('"')) + '"');
  auto keyword = token("keyword", choice("null", "false", "true"));
  auto array = token("array", op('[') + repeat(expr, op(',')) + op(']'));
  auto property = token("property", string + op(':') + expr);
  auto object = token("object", op('{') + repeat(property, op(',')) + op('}'));
  expr = number | string | keyword | array | object;

  auto res = expr(text);
  token.print();
  return res;
}

constexpr auto input = R""""(
{
  "id": 1,
  "name": "Hello",
  "tags": [
    {
      "key": "score",
      "value": 2
    }
  ]
}
)"""";
auto cv = cf("{\"id\": 1, \"vals\": [null, 2]}");

#include <iostream>
int main() {
  std::cout << cv.value_or(-1) << '\n';
  return 0;
}

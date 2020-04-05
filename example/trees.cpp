#include <iostream>

#include "alex/alex.h"
#include "alext/alext.h"

using token = int;

template<>
token alex::token_root<token>() {
  return 0;
}

using token_tree_builder
  = alex::token_tree_builder<token, alex::token_tree_fixed_capacity>;

using token_tree = token_tree_builder::tree_type;

void print_tree(token_tree::node u, int d) {
  for (int i = 0; i < d; i++) std::cout << "  ";

  std::cout << u.data().token() << '\n';
  for(auto v : u.children())
    print_tree(v, d + 1);
}

int main() {
  auto T = token_tree_builder(20);
  
  auto p1 = T.branch(1);
    auto p2 = T.branch(2);
      auto p3 = T.branch(3);
      T.commit(p3, "");
      auto p4 = T.branch(4);
      T.commit(p4, "");
      auto p5 = T.branch(5);
        auto p6 = T.branch(6);
        T.commit(p6, "");
      T.commit(p5, "");
    T.commit(p2, "");
  T.commit(p1, "");
  auto p7 = T.branch(7);
    auto p8 = T.branch(8);
      auto p9 = T.branch(9);
      T.commit(p9, "");
      auto p10 = T.branch(10);
      T.commit(p10, "");
      auto p11 = T.branch(11);
      T.commit(p11, "");
    T.commit(p8, "");
    auto p12 = T.branch(12);
      auto p13 = T.branch(13);
      T.commit(p13, "");
    T.commit(p12, "");
  T.commit(p7, "");

  auto t = T.finish();
  print_tree(t.root(), 0);
}

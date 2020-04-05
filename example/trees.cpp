#include <iostream>

#include "alex/alex.h"
#include "alext/alext.h"

using token = int;

template<>
token alex::token_root<token>() {
  return 0;
}

void print_tree(alex::token_tree<token>::node u, int d) {
  for (int i = 0; i < d; i++) std::cout << "  ";

  std::cout << u.data().token() << '\n';
  for(auto v : u.children())
    print_tree(v, d + 1);
}

int main() {
  auto T = alex::token_tree_builder<token>();
  
  auto p1 = T.branch();
    auto p2 = T.branch();
      auto p3 = T.branch();
      T.commit(p3, 3, "");
      auto p4 = T.branch();
      T.commit(p4, 4, "");
      auto p5 = T.branch();
        auto p6 = T.branch();
        T.commit(p6, 6, "");
      T.commit(p5, 5, "");
    T.commit(p2, 2, "");
  T.commit(p1, 1, "");
  auto p7 = T.branch();
    auto p8 = T.branch();
      auto p9 = T.branch();
      T.commit(p9, 9, "");
      auto p10 = T.branch();
      T.commit(p10, 10, "");
      auto p11 = T.branch();
      T.commit(p11, 11, "");
    T.commit(p8, 8, "");
    auto p12 = T.branch();
      auto p13 = T.branch();
      T.commit(p13, 13, "");
    T.commit(p12, 12, "");
  T.commit(p7, 7, "");

  auto t = T.finish();
  print_tree(t.root(), 0);
}

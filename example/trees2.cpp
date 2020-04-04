#include <vector>
#include <memory>
#include "alex/alex.h"
#include "alext/alext.h"









using tree = alex::token_tree;

#include <iostream>
void print_tree(tree::node u, int d) {
  for (int i = 0; i < d; i++) std::cout << "  ";
  std::cout << u.value() << '\n';

  for (auto v : u)
    print_tree(v, d + 1);
}

void print_tree(tree::node u) {
  for (auto v : u)
    print_tree(v);
}

int main() {
  tree T;
  
  auto p0 = T.add(0);
    auto p1 = T.add(1);
      auto p2 = T.add(2);
        auto p3 = T.add(3);
        T.commit(p3);
        auto p4 = T.add(4);
        T.commit(p4);
        auto p5 = T.add(5);
          auto p6 = T.add(6);
          T.commit(p6);
        T.commit(p5);
      T.commit(p2);
    T.commit(p1);
    auto p7 = T.add(7);
      auto p8 = T.add(8);
        auto p9 = T.add(9);
        T.commit(p9);
        auto p10 = T.add(10);
        T.commit(p10);
        auto p11 = T.add(11);
        T.commit(p11);
      T.commit(p8);
      auto p12 = T.add(12);
        auto p13 = T.add(13);
        T.commit(p13);
      T.commit(p12);
    T.commit(p7);
  T.commit(p0);

  print_tree(T.root(), 0);
}

#include <vector>

struct node {
  int val;
  int end;
};

struct tree {
  node buffer[14];
  int pos;
};

auto add(int val, tree& T) {
  T.buffer[T.pos].val = val;
  return T.pos++;
}

auto fin(int pos, tree& T) {
  T.buffer[pos].end = T.pos;
}

auto rev(int pos, tree& T) {
  T.pos = pos;
}

auto min(int x, int y) {
  return x < y ? x : y;
}

#include <iostream>
#include <string>
void out(tree& T, int i = 0, int d = 0, std::string p = "") {
  int itr = i + 1;
  int end = T.buffer[i].end;
  while (itr != end) {
    node& u = T.buffer[itr];
    std::cout << p << "+--" << u.val << '\n';
    out(T, itr, d + 1, p + ((end != u.end) ? "|  " : "   "));
    itr = u.end;
  }
}

int main() {
  auto T = tree();
  T.pos = 0;

  int p0 = add(0, T);
    int p1 = add(1, T);
      int p2 = add(2, T);
        int p3 = add(3, T);
        fin(p3, T);
        int p4 = add(4, T);
        fin(p4, T);
        int p5 = add(5, T);
          int p6 = add(6, T);
          fin(p6, T);
        fin(p5, T);
      fin(p2, T);
    //fin(p1, T);
    rev(p1, T);
    int p7 = add(7, T);
      int p8 = add(8, T);
        int p9 = add(9, T);
        fin(p9, T);
        int p10 = add(10, T);
        fin(p10, T);
        int p11 = add(11, T);
        fin(p11, T);
      fin(p8, T);
      int p12 = add(12, T);
        int p13 = add(13, T);
        fin(p13, T);
      fin(p12, T);
    fin(p7, T);
  fin(p0, T);

  out(T);

  return 0;
}
#include <string_view>
#include <iostream>
#include "lt3/alex.h"

using namespace lt3;



int main()
{
  auto recr = alex::recursive();
  recr = alex::grammar<char>('a') + recr;

  auto leaf = alex::repeat(alex::from_to('a', 'z'), 1);
  auto tree = alex::recursive();
  tree = '[' + alex::repeat(leaf || tree) + ']';

  //std::cout << alex::parse("[a[b[c]]]", tree);
}

#include <iostream>
#include "alex/alex.h"

int main()
{
  auto R = alex::recursive();
  R = 'a' + alex::optional(R);

  std::cout << alex::parse("a",   R + alex::eof());
  std::cout << alex::parse("aaa", R + alex::eof());
}

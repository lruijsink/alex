#include <string_view>
#include <iostream>
#include "lt3/alex.h"

using namespace lt3;

int main()
{
  auto leaf = alex::repeat(alex::from_to('a', 'z'), 1);

  auto adpt = alex::grammar_adapter_impl<decltype(leaf)>(leaf);
}

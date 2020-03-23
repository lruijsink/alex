#include <memory>
#include "alex/alex.h"

//#include "lt3/alex/grammar.h"

using namespace alex;

int main()
{
  auto number = from_to('1', '9') + repeat(from_to('0', '9'));
  parse("123", number);
}

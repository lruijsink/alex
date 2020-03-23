#include <memory>
#include "lt3/alex.h"

//#include "lt3/alex/grammar.h"

using namespace lt3::alex;

int main()
{
  auto number = from_to('1', '9') + repeat(from_to('0', '9'));
  parse("123", number);
}

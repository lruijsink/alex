#pragma once

#include <type_traits>

#include "defines.h"
#include "grammar.h"

namespace ALEX_NAMESPACE_NAME {


template<>
struct grammar<std::true_type>
{
  bool read_and_test(reader&)
  {
    return true;
  }
};

template<>
struct grammar<std::false_type>
{
  bool read_and_test(reader&)
  {
    return false;
  }
};


}

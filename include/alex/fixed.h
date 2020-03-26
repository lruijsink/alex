#pragma once

#include <type_traits>

#include "defines.h"
#include "grammar.h"

namespace ALEX_NAMESPACE_NAME {


template<>
struct grammar<std::true_type>
{
  template<class... TS>
  bool read_and_test(reader<TS...>)
  {
    return true;
  }
};

template<>
struct grammar<std::false_type>
{
  template<class... TS>
  bool read_and_test(reader<TS...>)
  {
    return false;
  }
};


}

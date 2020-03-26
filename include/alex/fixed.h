#pragma once

#include <type_traits>

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


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


ALEX_NAMESPACE_END

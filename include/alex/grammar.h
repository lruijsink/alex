#pragma once

#include <type_traits>
#include "defines.h"

namespace ALEX_NAMESPACE_NAME {


namespace detail
{
  class reader;
}

template<class T, class... TS>
class grammar
{
public:
  grammar(T, TS...) = delete;
};

template<class T>
class grammar<T>
{
public:
  grammar(T fnc) : fnc_(fnc) {}

  bool read_and_test(detail::reader& r) const
  {
    return fnc_(r);
  }

private:
  T fnc_;
};


}

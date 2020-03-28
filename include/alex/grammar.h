#pragma once

#include <type_traits>
#include "defines.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


template<class T>
class grammar<T>
{
public:
  grammar(T fnc) : fnc_(fnc) {}

  bool read_and_test(reader& r) const
  {
    return fnc_(r);
  }

private:
  static constexpr bool is_fnc = std::is_invocable_v<T, reader&>;

  std::enable_if_t<is_fnc, T> fnc_;
};


}

#pragma once

#include <type_traits>
#include "defines.h"
#include "reader.h"
#include "reader_abstract.h"

namespace ALEX_NAMESPACE_NAME {


template<class T>
class grammar<T>
{
public:
  grammar(T fnc) : fnc_(fnc) {}

  template<class... TS>
  bool read_and_test(reader<TS...> r) const
  {
    return fnc_(r);
  }

private:
  static constexpr bool is_fnc =
    std::is_invocable_v<T, reader<tag::poly>>;

  std::enable_if_t<is_fnc, T> fnc_;
};


}

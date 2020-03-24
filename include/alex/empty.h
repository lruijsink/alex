#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


namespace tag
{
  template<bool V>
  struct empty;
}

template<bool V>
class grammar<tag::empty<V>>
{
public:
  template<class... TS>
  bool match(reader<TS...>)
  {
    return V;
  }
};

inline auto empty_true()
{
  return grammar<tag::empty<true>>();
}

inline auto empty_false()
{
  return grammar<tag::empty<false>>();
}


ALEX_NAMESPACE_END

#pragma once

#include "defines.h"
#include "grammar.h"

namespace ALEX_NAMESPACE_NAME {


template<class... TS>
auto seq(TS... gs)
{
  return grammar([=] (auto& r)
  {
    return (r.parse(grammar(gs)) && ...);
  });
}

template<class L, class R>
auto operator+(L lhs, R rhs)
{
  return seq(lhs, rhs);
}

template<class T>
auto operator+(bool, grammar<T>) = delete;

template<class T>
auto operator+(grammar<T>, bool) = delete;


}

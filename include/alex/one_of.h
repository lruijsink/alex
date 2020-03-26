#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


template<class... GrammarTS>
auto one_of(GrammarTS... gs)
{
  return grammar([=] (auto r)
  {
    return (... || r.parse(grammar(gs)));
  });
}

template<class L, class R>
auto operator||(L lhs, R rhs)
{
  return one_of(lhs, rhs);
}

template<class T>
auto operator||(bool, grammar<T>) = delete;

template<class T>
auto operator||(grammar<T>, bool) = delete;


ALEX_NAMESPACE_END

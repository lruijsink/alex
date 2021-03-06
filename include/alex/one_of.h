#pragma once

#include "defines.h"
#include "grammar.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


template<class... GrammarTS>
auto one_of(GrammarTS... gs)
{
  return grammar([=] (detail::reader& r)
  {
    return (... || r.match(grammar(gs)));
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


}

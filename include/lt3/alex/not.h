#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class GrammarT>
auto not(GrammarT g)
{
  return grammar([=] (auto r)
  {
    return !grammar(g).match(r);
  });
}


LT3_ALEX_NAMESPACE_END

#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


template<class GrammarT>
auto not(GrammarT g)
{
  return grammar([=] (auto r)
  {
    return !grammar(g).match(r);
  });
}


ALEX_NAMESPACE_END

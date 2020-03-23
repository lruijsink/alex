#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class... GrammarTS>
auto optional(GrammarTS... gs)
{
  return grammar([=] (auto r)
  {
    return (... || r.parse(grammar(gs))) || true;
  });
}


LT3_ALEX_NAMESPACE_END

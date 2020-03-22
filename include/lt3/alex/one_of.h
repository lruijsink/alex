#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class... GrammarTS>
auto one_of(GrammarTS... gs)
{
  return grammar([=] (auto& parser)
  {
    return (... || parser.parse(grammar(gs)));
  });
}


LT3_ALEX_NAMESPACE_END

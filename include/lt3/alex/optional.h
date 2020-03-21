#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class GrammarT>
auto optional(GrammarT g)
{
  return grammar([=] (auto& parser)
  {
    parser.parse(g);
    return true;
  });
}


LT3_ALEX_NAMESPACE_END

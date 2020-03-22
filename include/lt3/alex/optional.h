#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class... GrammarTS>
auto optional(GrammarTS... grammars)
{
  return grammar([=] (auto& parser)
  {
    return (... || parser.parse(grammars)) || true;
  });
}


LT3_ALEX_NAMESPACE_END

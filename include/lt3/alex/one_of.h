#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class... GrammarTS>
auto one_of(GrammarTS... grammars)
{
  return grammar([=] (auto& parser)
  {
    return (... || parser.parse(grammars));
  });
}


LT3_ALEX_NAMESPACE_END

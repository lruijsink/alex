#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class GrammarT>
auto symbol(std::string name, GrammarT g)
{
  return grammar([=] (auto& parser)
  {
    return parser.parse(g);
  });
}


LT3_ALEX_NAMESPACE_END

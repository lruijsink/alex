#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class GrammarT>
auto repeat(GrammarT g, int min_count)
{
  return grammar([=] (auto& parser)
  {
    int count = 0;
    while (parser.parse(g) && !parser.stream().eof())
    {
      count++;
    }
    return count >= min_count;
  });
}

template<class GrammarT>
auto repeat(GrammarT g)
{
  return repeat(g, 1);
}


LT3_ALEX_NAMESPACE_END

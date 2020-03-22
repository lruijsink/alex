#pragma once

#include "defines.h"
#include "grammar.h"
#include "optional.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class GrammarT>
auto repeat(GrammarT g, int min_count = 0)
{
  auto G = grammar(g);
  return grammar([=] (auto& parser)
  {
    int c = 0;
    while (parser.parse(G) && !parser.stream().eof())
      c++;
    return c >= min_count;
  });
}

template<class GrammarT, class DelimT>
auto repeat(GrammarT g, DelimT d, int min_count = 0)
{
  auto G = grammar(g);
  auto D = grammar(d);
  return grammar([=] (auto& parser)
  {
    int c = 0;
    while (c == 0 ? parser.parse(G) : parser.parse(D + G) && !parser.stream().eof())
      c++;
    return c >= min_count;
  });
}


LT3_ALEX_NAMESPACE_END

#pragma once

#include "defines.h"
#include "grammar.h"
#include "optional.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class GrammarT>
auto repeat(GrammarT g, int min_count = 0)
{
  auto G = grammar(g);
  return grammar([=] (auto r)
  {
    int c = 0;
    while (r.parse(G) && !r.eof())
      c++;
    return c >= min_count;
  });
}

template<class GrammarT, class DelimT>
auto repeat(GrammarT g, DelimT d, int min_count = 0)
{
  auto G = grammar(g);
  auto D = grammar(d);
  return grammar([=] (auto r)
  {
    int c = 0;
    while (c == 0 ? r.parse(G) : r.parse(D + G) && !r.eof())
      c++;
    return c >= min_count;
  });
}


LT3_ALEX_NAMESPACE_END

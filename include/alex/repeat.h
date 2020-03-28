 #pragma once

#include "defines.h"
#include "grammar.h"
#include "fixed.h"

namespace ALEX_NAMESPACE_NAME {


template<class T>
auto repeat(T g)
{
  auto G = grammar(g);
  return grammar([=] (auto& r)
  {
    while (r.parse(G))
    {
    }

    return true;
  });
}

template<class T, class S>
auto repeat(T g, S s)
{
  auto G = grammar(g);
  auto S_G = grammar(s) + G;
  return grammar([=] (auto& r)
  {
    if (!r.parse(G))
      return true;
    
    while (r.parse(S_G))
    {
    }
    
    return true;
  });
}

}

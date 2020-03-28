 #pragma once

#include "defines.h"
#include "grammar.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


template<class T>
auto repeat(T g)
{
  auto G = grammar(g);
  return grammar([=] (detail::reader& r)
  {
    while (r.match(G))
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
  return grammar([=] (detail::reader& r)
  {
    if (!r.match(G))
      return true;
    
    while (r.match(S_G))
    {
    }
    
    return true;
  });
}

}

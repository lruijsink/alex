#pragma once

#include "defines.h"
#include "grammar.h"

namespace ALEX_NAMESPACE_NAME {


template<class T>
auto optional(T g)
{
  auto G = grammar(g);
  return grammar([=] (auto& r)
  {
    r.match(G);
    return true;
  });
}


}

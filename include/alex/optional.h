#pragma once

#include "defines.h"
#include "grammar.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


template<class T>
auto optional(T g)
{
  auto G = grammar(g);
  return grammar([=] (detail::reader& r)
  {
    r.match(G);
    return true;
  });
}


}

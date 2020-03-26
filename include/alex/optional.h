#pragma once

#include "defines.h"
#include "grammar.h"

namespace ALEX_NAMESPACE_NAME {


template<class... GrammarTS>
auto optional(GrammarTS... gs)
{
  return grammar([=] (auto r)
  {
    return (... || r.parse(grammar(gs))) || true;
  });
}


}

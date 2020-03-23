#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


template<class GrammarT>
auto symbol(std::string name, GrammarT g)
{
  return grammar([=] (auto r)
  {
    return r.parse(g);
  });
}


ALEX_NAMESPACE_END

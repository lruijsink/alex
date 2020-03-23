#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


template<class CharT>
auto from_to(CharT from, CharT to)
{
  return grammar([=] (auto r)
  {
    auto v = r.get();
    return from <= v && v <= to;
  });
};


ALEX_NAMESPACE_END

#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class CharT>
auto from_to(CharT from, CharT to)
{
  return grammar([=] (auto& parser)
  {
    auto v = parser.stream().get();
    return from <= v && v <= to;
  });
};


LT3_ALEX_NAMESPACE_END

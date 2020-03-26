#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


template<class CharT>
auto from_to(CharT from, CharT to)
{
  return grammar([=] (auto r) {
    auto c = r.get();
    return from <= c && c <= to;
  });
};


ALEX_NAMESPACE_END

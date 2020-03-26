#pragma once

#include "defines.h"
#include "grammar.h"

namespace ALEX_NAMESPACE_NAME {


template<class CharT>
auto from_to(CharT from, CharT to)
{
  return grammar([=] (auto r) {
    auto c = r.get();
    return from <= c && c <= to;
  });
};


}

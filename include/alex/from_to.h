#pragma once

#include "defines.h"
#include "grammar.h"

namespace ALEX_NAMESPACE_NAME {


inline auto from_to(char from, char to)
{
  return grammar([=] (auto& r) {
    auto c = r.get();
    return from <= c && c <= to;
  });
};


}

#pragma once

#include "defines.h"
#include "grammar.h"

namespace ALEX_NAMESPACE_NAME {


template<class... TS>
inline auto any_but(TS... cs)
{
  return grammar([=] (auto& r)
  {
    return !r.eof() && !((r.get() == static_cast<char>(cs)) || ...);
  });
}


}

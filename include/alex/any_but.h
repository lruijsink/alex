#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


template<class... TS>
inline auto any_but(TS... cs)
{
  return grammar([=] (auto r)
  {
    return !r.eof() && !((r.get() == static_cast<char>(cs)) || ...);
  });
}


ALEX_NAMESPACE_END

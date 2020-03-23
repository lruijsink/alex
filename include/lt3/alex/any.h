#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


inline auto any()
{
  return grammar([=] (auto r)
  {
    if (r.eof())
      return false;
    r.get();
    return true;
  });
}


LT3_ALEX_NAMESPACE_END

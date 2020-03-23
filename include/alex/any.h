#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


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


ALEX_NAMESPACE_END

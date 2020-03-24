#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


inline auto eof()
{
  return grammar([=] (auto r)
  {
    return r.eof();
  });
}


ALEX_NAMESPACE_END

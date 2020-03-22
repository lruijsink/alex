#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


inline auto any()
{
  return grammar([=] (auto& parser)
  {
    if (parser.stream().eof())
      return false;
    parser.stream().get();
    return true;
  });
}


LT3_ALEX_NAMESPACE_END

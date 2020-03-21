#pragma once

#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class CharT>
auto character(CharT c)
{
  return grammar([=] (auto& parser)
  {
    return parser.stream().get() == c;
  });
}


LT3_ALEX_NAMESPACE_END

#pragma once

#include "defines.h"

LT3_ALEX_NAMESPACE_BEGIN


class character
{
public:
  character(char c)
    : c_(c)
  {
  }

  template<class ParserT>
  bool match(ParserT parser) const
  {
    return parser.stream().get() == c_;
  }

private:
  char c_;
};


LT3_ALEX_NAMESPACE_END

#pragma once

#include <string>
#include <string_view>
#include "defines.h"
#include "parser.h"

ALEX_NAMESPACE_BEGIN


template<class GrammarT>
auto match(const char* str, GrammarT g)
{
  auto source = std::string_view(str);
  return parser(source).match(g);
}


ALEX_NAMESPACE_END

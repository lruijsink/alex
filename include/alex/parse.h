#pragma once

#include <string>
#include <string_view>
#include "defines.h"
#include "parser.h"

ALEX_NAMESPACE_BEGIN


template<class SourceT, class GrammarT>
auto match(SourceT str, GrammarT g)
{
  auto src = buffer_source(str);
  auto srm = buffer_stream(src);
  auto prs = parser(srm);
  return prs.match(g);
}

template<class GrammarT, size_t N>
auto match(const char (&str)[N], GrammarT g)
{
  auto src = buffer_source<char[N]>(str);
  auto srm = buffer_stream(src);
  auto prs = parser(srm);
  return prs.match(g);
}


ALEX_NAMESPACE_END

#pragma once

#include <string>
#include <string_view>
#include "defines.h"
#include "parser.h"

namespace ALEX_NAMESPACE_NAME {


template<class SourceT, class GrammarT>
auto match(SourceT str, GrammarT g)
{
  auto prs = parser(str);
  return prs.match(g);
}

template<class GrammarT, size_t N>
auto match(const char (&str)[N], GrammarT g)
{
  auto prs = parser(str);
  return prs.match(g);
}

template<class SourceT, class GrammarT>
auto parse(SourceT str, GrammarT g)
{
  auto prs = parser(str);
  return prs.parse(g);
}

template<class GrammarT, size_t N>
auto parse(const char (&str)[N], GrammarT g)
{
  auto prs = parser(str);
  return prs.parse(g);
}


}

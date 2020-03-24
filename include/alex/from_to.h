#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


template<class CharT>
struct from_to_maker
{
  char from;

  auto to(CharT to)
  {
    return grammar([=] (auto r)
    {
      auto v = r.get();
      return from <= v && v <= to;
    });
  }
};

template<class CharT>
auto from(CharT from)
{
  return from_to_maker<CharT>{ from };
};


ALEX_NAMESPACE_END

#pragma once

#include "defines.h"
#include "grammar.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


template<class... TS>
inline auto any_but(TS... cs)
{
  return grammar([=] (detail::reader& r)
  {
    return !r.eof() && !((r.get() == static_cast<char>(cs)) || ...);
  });
}


}

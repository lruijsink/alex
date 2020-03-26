#pragma once

#include "defines.h"
#include "grammar.h"

namespace ALEX_NAMESPACE_NAME {


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


}

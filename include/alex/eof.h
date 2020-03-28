#pragma once

#include "defines.h"
#include "grammar.h"

namespace ALEX_NAMESPACE_NAME {


inline auto eof()
{
  return grammar([=] (auto& r)
  {
    return r.eof();
  });
}


}

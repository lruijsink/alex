#pragma once

#include "defines.h"
#include "grammar.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


inline auto any()
{
  return grammar([=] (detail::reader& r)
  {
    if (r.eof())
      return false;
    r.get();
    return true;
  });
}


}

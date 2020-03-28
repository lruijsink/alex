#pragma once

#include "defines.h"
#include "grammar.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


inline auto eof()
{
  return grammar([=] (detail::reader& r)
  {
    return r.eof();
  });
}


}

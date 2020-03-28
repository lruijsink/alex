#pragma once

#include <string_view>
#include <optional>
#include "defines.h"
#include "grammar.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


class parser
{
public:
  template<class T>
  auto match(std::string_view s, T g)
  {
    return detail::reader(s).match(grammar(g) + eof());
  }

  template<class T>
  auto parse(std::string_view s, T g) -> std::optional<symbol_tree>
  {
    auto r = detail::reader(s);
    if (!r.match(g))
      return std::nullopt;

    return r.tree();
  }
};


}

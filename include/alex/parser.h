#pragma once

#include <string_view>
#include "defines.h"
#include "grammar.h"
#include "reader.h"
#include "symbol_tree.h"

namespace ALEX_NAMESPACE_NAME {


class parser
{
public:
  parser(std::string_view source)
    : source_(source)
  {
  }

  parser(const parser&) = delete;
  parser(parser&&) = delete;

  template<class... TS>
  bool match(grammar<TS...> g)
  {
    auto smt = symbol_tree();
    return reader(source_, &smt).parse(g);
  }

  template<class... TS>
  auto parse(grammar<TS...> g)
  {
    auto smt = symbol_tree();
    reader(source_, &smt).parse(g);
    return smt;
  }

private:
  std::string_view source_;
};


}

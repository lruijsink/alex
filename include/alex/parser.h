#pragma once

#include "defines.h"

#include "grammar.h"
#include "reader.h"
#include "stream.h"
#include "symbol_tree.h"

namespace ALEX_NAMESPACE_NAME {


template<class StreamT>
class parser
{
public:
  using stream_type = StreamT;
  using char_type   = typename stream_type::char_type;

  parser(stream_type stream)
    : stream_(stream)
  {
  }

  parser(const parser&) = delete;
  parser(parser&&) = delete;

  template<class... TS>
  bool match(grammar<TS...> g)
  {
    auto smt = symbol_tree();
    return reader<stream_type>(stream_, &smt).parse(g);
  }

  template<class... TS>
  auto parse(grammar<TS...> g)
  {
    auto smt = symbol_tree();
    reader<stream_type>(stream_, &smt).parse(g);
    return smt;
  }

private:
  stream_type stream_;
};


}

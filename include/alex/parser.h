#pragma once

#include "defines.h"
#include "stream.h"
#include "reader.h"
#include "grammar.h"

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
    return reader<stream_type>(stream_).parse(g);
  }

private:
  stream_type stream_;
};


}

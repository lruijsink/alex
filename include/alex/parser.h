#pragma once

#include "defines.h"
#include "stream.h"
#include "reader.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


template<class SourceT>
class parser
{
public:
  using source_type = SourceT;
  using stream_type = stream<source_type>;
  using char_type   = typename stream_type::char_type;

  parser(source_type& source)
    : stream_(source)
  {
  }

  parser(const parser&) = delete;
  parser(parser&&) = delete;

  template<class... TS>
  bool match(grammar<TS...> g)
  {
    return reader<decltype(stream_)>(stream_).parse(g);
  }

private:
  stream_type stream_;
};


ALEX_NAMESPACE_END

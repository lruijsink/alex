#pragma once

#include "defines.h"
#include "grammar.h"
#include "tag.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class ParserT>
class reader
{
public:
  using parser_type = ParserT;
  using stream_type = typename parser_type::stream_type;
  using traits_type = typename stream_type::traits_type;
  using char_type   = typename traits_type::char_type;
  using int_type    = typename traits_type::int_type;

  reader(parser_type& parser, stream_type& stream)
    : parser_(parser)
    , stream_(stream)
  {
  }

  auto get() -> int_type
  {
    return stream_.get();
  }

  auto eof() -> bool
  {
    return stream_.eof();
  }

  template<class T>
  auto parse(grammar<T> g) -> bool
  {
    stream_.fork();
    auto matches = g.match(*this);

    if (matches)
      stream_.join();
    else
      stream_.reset();

    return matches;
  }

private:
  parser_type& parser_;
  stream_type& stream_;
};


LT3_ALEX_NAMESPACE_END

#pragma once

#include "defines.h"
#include "stream.h"
#include "literal.h"

LT3_ALEX_NAMESPACE_BEGIN


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

  template<class G>
  bool parse(grammar<G> grammar)
  {
    stream_.fork();
    auto matches = grammar.match(*this);

    if (matches)
      stream_.join();
    else
      stream_.reset();

    return matches;
  }

  template<class T>
  bool parse(T value)
  {
    return parse(grammar(value));
  }

  stream_type& stream()
  {
    return stream_;
  }

private:
  stream_type stream_;
};


LT3_ALEX_NAMESPACE_END

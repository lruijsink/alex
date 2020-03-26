#pragma once

#include "defines.h"
#include "grammar.h"

ALEX_NAMESPACE_BEGIN


template<class StreamT>
class reader<StreamT>
{
public:
  using stream_type = StreamT;
  using traits_type = typename stream_type::traits_type;
  using char_type   = typename traits_type::char_type;
  using int_type    = typename traits_type::int_type;

  reader(stream_type& stream)
    : stream_(stream)
  {
  }

  auto get()
  {
    return stream_.get();
  }

  auto eof() const
  {
    return stream_.eof();
  }

  template<class... TS>
  auto parse(grammar<TS...> g)
  {
    auto fork_point = stream_.fork();
    auto matches = g.read_and_test(*this);

    if (matches)
      stream_.join(fork_point);
    else
      stream_.reset(fork_point);

    return matches;
  }

private:
  stream_type& stream_;
};


ALEX_NAMESPACE_END

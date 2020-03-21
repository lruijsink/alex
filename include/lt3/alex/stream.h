#pragma once

#include <type_traits>
#include "defines.h"
#include "stream_traits.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class SourceT>
class stream
{
public:
  using source_type = SourceT;
  using stream_type = make_fork_streamable<source_type>;
  using char_type   = typename stream_type::char_type;
  using traits_type = std::char_traits<char_type>;
  using int_type    = typename traits_type::int_type;

  stream(source_type& source)
    : stream_(source)
  {
  }

  stream(source_type&&) = delete;

  auto get() -> int_type
  {
    return stream_.get();
  }

  auto eof()
  {
    return stream_.eof();
  }

  auto fork()
  {
    stream_.fork();
  }

  auto join()
  {
    stream_.join();
  }

  auto reset()
  {
    stream_.reset();
  }

private:
  stream_type stream_;
};


LT3_ALEX_NAMESPACE_END

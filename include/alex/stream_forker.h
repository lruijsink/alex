#pragma once

#include "defines.h"
#include "stream_buffer.h"

ALEX_NAMESPACE_BEGIN


template<class SourceT>
class stream_forker
{
public:
  using source_type = SourceT;
  using char_type   = typename source_type::char_type;
  using traits_type = std::char_traits<char_type>;
  using int_type    = typename traits_type::int_type;

  stream_forker(source_type& source)
    : source_(source)
  {
  }

  stream_forker(source_type&&) = delete;

  auto get() -> int_type
  {
    if (buffer_.available())
      return buffer_.get();
    
    auto next = source_.get();
    if (next == traits_type::eof())
      return traits_type::eof();
    
    buffer_.put(next);
    return next;
  }

  auto eof() const
  {
    return !buffer_.available() && source_.eof();
  }

  auto fork()
  {
    buffer_.fork();
  }

  auto join()
  {
    buffer_.join();
  }

  auto reset()
  {
    buffer_.reset();
  }

private:
  source_type& source_;
  stream_buffer<char_type> buffer_;
};


ALEX_NAMESPACE_END

#pragma once

#include "defines.h"
#include "buffer_source.h"

ALEX_NAMESPACE_BEGIN


template<class SourceT>
class buffer_stream
{
public:
  using source_type = SourceT;
  using value_type  = typename source_type::value_type;
  using traits_type = std::char_traits<value_type>;
  using char_type   = typename traits_type::char_type;
  using int_type    = typename traits_type::int_type;
  using iterator    = typename source_type::iterator;

  buffer_stream(source_type b)
    : it_(b.begin())
    , eof_(b.end())
  {
  }

  auto get() -> int_type
  {
    return it_ != eof_ ? *(it_++) : traits_type::eof();
  }

  auto eof()
  {
    return it_ == eof_;
  }

  auto fork()
  {
    return it_;
  }

  auto join(iterator)
  {
  }

  auto reset(iterator fork_point)
  {
    it_ = fork_point;
  }

private:
  iterator it_;
  iterator eof_;
};


ALEX_NAMESPACE_END

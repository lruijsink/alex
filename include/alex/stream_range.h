#pragma once

#include <stack>
#include "defines.h"

ALEX_NAMESPACE_BEGIN


template<class SourceT>
class stream_range
{
public:
  using source_type = SourceT;
  using char_type   = typename source_type::value_type;
  using traits_type = std::char_traits<char_type>;
  using int_type    = typename traits_type::int_type;

private:
  using source_iterator = decltype(std::declval<source_type>().begin());
  using source_sentinel = decltype(std::declval<source_type>().begin());

public:
  stream_range(const source_type& source)
    : it_(source.begin())
    , end_(source.end())
  {
  }

  stream_range(source_type&&) = delete;

  auto get() -> int_type
  {
    return it_ != end_
         ? *(it_++)
         : traits_type::eof();
  }

  auto eof() const
  {
    return it_ == end_;
  }

  auto fork()
  {
    forks_.push(it_);
  }

  auto join()
  {
    forks_.pop();
  }

  auto reset()
  {
    it_ = forks_.top();
    forks_.pop();
  }

private:
  source_iterator it_;
  source_sentinel end_;
  std::stack<source_iterator> forks_;
};


ALEX_NAMESPACE_END

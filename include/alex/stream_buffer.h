#pragma once

#include <stack>
#include <vector>
#include "defines.h"

ALEX_NAMESPACE_BEGIN


template<class ValueT>
class stream_buffer
{
public:
  using value_type = ValueT;

  struct fork_point
  {
    size_t reset_position;
  };

  stream_buffer()
    : position_(0)
  {
  }

  auto available() const
  {
    return position_ != buffer_.size();
  }

  auto get()
  {
    return buffer_.at(position_++);
  }

  auto put(value_type value)
  {
    if (forks_.empty())
      return;

    position_++;
    buffer_.push_back(value);
  }

  auto fork()
  {
    if (forks_.empty())
    {
      position_ = 0;
      buffer_.clear();
    }
    forks_.push(fork_point{ position_ });
  }

  auto join()
  {
    forks_.pop();
  }

  auto reset()
  {
    auto fork = forks_.top();
    forks_.pop();
    position_ = fork.reset_position;
  }

private:
  size_t position_;
  std::stack<fork_point> forks_;
  std::vector<value_type> buffer_;
};


ALEX_NAMESPACE_END

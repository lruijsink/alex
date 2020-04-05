#pragma once

namespace alex {
namespace detail {


template<class IteratorType, class SentinelType>
class iterator_range {
public:
  using iterator = IteratorType;
  using sentinel = SentinelType;

  iterator_range(iterator begin_itr, sentinel end_itr)
    : begin_(begin_itr)
    , end_(end_itr) {}

  auto begin() const {
    return begin_;
  }

  auto end() const {
    return end_;
  }

private:
  iterator begin_;
  sentinel end_;
};


}
}

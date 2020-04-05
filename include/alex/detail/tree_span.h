#pragma once

namespace alex {
namespace detail {


template<class IteratorType>
class tree_span {
public:
  using iterator = IteratorType;

  tree_span(iterator begin_itr, iterator end_itr)
    : begin_(begin_itr), end_(end_itr) {}

  auto begin() const {
    return begin_;
  }

  auto end() const {
    return end_;
  }

private:
  iterator begin_;
  iterator end_;
};


}
}

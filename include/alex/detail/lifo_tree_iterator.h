#pragma once

#include "./lifo_tree_sentinel.h"

namespace alex {
namespace detail {


template<class NodeType>
class lifo_tree_iterator {
public:
  using value_type = NodeType;
  using container_type = typename value_type::container_type;

  lifo_tree_iterator(const container_type& container, size_t index)
    : container_(container)
    , index_(index) {}

  auto operator*() const {
    return value_type(container_, index_);
  }

  auto operator++() {
    index_ = container_[index_].next_index;
  }

  auto operator!=(lifo_tree_sentinel sentinel) const {
    return index_ != sentinel.index();
  }

private:
  const container_type& container_;
  size_t index_;
};


}
}

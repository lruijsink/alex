#pragma once

#include "./stack_tree_node.h"

namespace alex {
namespace detail {


template<class ContainerType>
class stack_tree_iterator {
public:
  stack_tree_iterator(const ContainerType& container, size_t index)
    : container_(container), index_(index) {}

  auto operator*() const {
    return stack_tree_node(container_, index_);
  }

  auto operator++() {
    index_ = container_[index_].neighbour_index;
  }

  auto operator!=(stack_tree_iterator other) const {
    return index_ != other.index_;
  }

private:
  const ContainerType& container_;
  size_t index_;
};


}
}

#pragma once

#include "./stack_tree_iterator.h"
#include "./tree_span.h"

namespace alex {
namespace detail {


template<class ContainerType>
class stack_tree_node {
public:
  stack_tree_node(const ContainerType& container, size_t index)
    : container_(container), index_(index) {}

  auto token() const {
    return container_[index_].value;
  }

  auto children() const {
    return tree_span<stack_tree_iterator<ContainerType>>(
      stack_tree_iterator(container_, index_ + 1),
      stack_tree_iterator(container_, container_[index_].neighbour_index));
  }

private:
  const ContainerType& container_;
  size_t index_;
};


}
}

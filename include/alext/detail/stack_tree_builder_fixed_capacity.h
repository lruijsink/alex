#pragma once

#include <memory>

#include "alex/detail/stack_tree_element.h"
#include "alex/detail/stack_tree_node.h"

namespace alex {
namespace detail {


template<class ValueType>
class stack_tree_builder_fixed_capacity {
public:
  using value_type = ValueType;
  using underlying_type = std::unique_ptr<stack_tree_element<value_type>[]>;
  using finished_type = stack_tree_container<underlying_type>;

  stack_tree_builder_fixed_capacity(size_t capacity)
    : container_(std::make_unique<stack_tree_element<value_type>[]>(capacity))
    , size_(0)
    , capacity_(capacity) {
    branch(0);
  }

  auto branch(value_type value) {
    container_[size_].value = value;
    return size_++;
  }

  auto commit(size_t branch_index) {
    container_[branch_index].neighbour_index = size_;
  }

  auto revert(size_t branch_index) {
    size_ = branch_index;
  }

  auto finish() {
    commit(0);
    return stack_tree_container(std::move(container_));
  }

private:
  underlying_type container_;
  size_t size_;
  size_t capacity_;
};


}
}

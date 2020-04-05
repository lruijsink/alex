#pragma once

#include <memory>

#include "alex/detail/lifo_tree.h"
#include "alex/detail/lifo_tree_element.h"
#include "alex/detail/lifo_tree_node.h"

namespace alex {
namespace detail {


template<class ValueType>
class fixed_capacity_lifo_tree_builder {
public:
  using value_type = ValueType;
  using container_type = std::unique_ptr<lifo_tree_element<value_type>[]>;
  using tree_type = lifo_tree<container_type>;

  fixed_capacity_lifo_tree_builder(size_t capacity)
    : container_(std::make_unique<lifo_tree_element<value_type>[]>(capacity))
    , size_(0)
    , capacity_(capacity) {
    branch(0);
  }

  auto branch(value_type value) {
    container_[size_].value = value;
    return size_++;
  }

  auto commit(size_t branch_index) {
    container_[branch_index].next_index = size_;
  }

  auto revert(size_t branch_index) {
    size_ = branch_index;
  }

  auto finish() {
    commit(0);
    return tree_type(std::move(container_));
  }

private:
  container_type container_;
  size_t size_;
  size_t capacity_;
};


}
}

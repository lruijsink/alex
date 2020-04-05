#pragma once

#include <memory>

#include "alex/detail/lifo_tree.h"
#include "alex/detail/lifo_tree_element.h"
#include "alex/detail/lifo_tree_node.h"

namespace alex {
namespace detail {


template<class ValueType>
class lifo_tree_fixed_capacity_builder {
public:
  using value_type = ValueType;
  using container_type = std::unique_ptr<lifo_tree_element<value_type>[]>;
  using tree_type = lifo_tree<container_type>;
  using marker_type = size_t;

  lifo_tree_fixed_capacity_builder(size_t capacity)
    : container_(std::make_unique<lifo_tree_element<value_type>[]>(capacity))
    , size_(0)
    , capacity_(capacity) {}

  auto branch() -> marker_type {
    return size_++;
  }

  auto commit(marker_type index, value_type value) {
    container_[index].value = value;
    container_[index].next_index = size_;
  }

  auto revert(marker_type index) {
    size_ = index;
  }

  auto finish() {
    return tree_type(std::move(container_));
  }

private:
  container_type container_;
  size_t size_;
  size_t capacity_;
};


}
}

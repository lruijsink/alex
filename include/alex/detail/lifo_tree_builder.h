#pragma once

#include <vector>

#include "./lifo_tree.h"
#include "./lifo_tree_element.h"
#include "./lifo_tree_node.h"

namespace alex {
namespace detail {


template<class ValueType>
class lifo_tree_builder {
public:
  using value_type = ValueType;
  using container_type = std::vector<lifo_tree_element<value_type>>;
  using tree_type = lifo_tree<container_type>;
  using marker_type = size_t;

  auto branch() -> marker_type {
    container_.emplace_back();
    return container_.size() - 1;
  }

  void commit(marker_type index, value_type value) {
    container_[index].value = value;
    container_[index].next_index = container_.size();
  }

  void revert(marker_type index) {
    container_.resize(index);
  }

  auto finish() {
    return tree_type(std::move(container_));
  }

private:
  container_type container_;
};


}
}

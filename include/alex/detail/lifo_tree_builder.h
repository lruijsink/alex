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

  lifo_tree_builder() {
    branch(0);
  }

  auto branch(value_type value) {
    container_.emplace_back().value = value;
    return container_.size() - 1;
  }

  void commit(size_t branch_index) {
    container_[branch_index].next_index = container_.size();
  }

  void revert(size_t branch_index) {
    container_.resize(branch_index);
  }

  auto finish() {
    commit(0);
    return tree_type(std::move(container_));
  }

private:
  container_type container_;
};


}
}

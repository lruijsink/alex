#pragma once

#include <vector>

#include "./stack_tree_container.h"
#include "./stack_tree_element.h"
#include "./stack_tree_node.h"

namespace alex {
namespace detail {


template<class ValueType>
class stack_tree_builder_vector {
public:
  using value_type = ValueType;
  using underlying_type = std::vector<stack_tree_element<value_type>>;
  using finished_type = stack_tree_container<underlying_type>;

  stack_tree_builder_vector() {
    branch(0);
  }

  auto branch(value_type value) {
    container_.emplace_back().value = value;
    return container_.size() - 1;
  }

  void commit(size_t branch_index) {
    container_[branch_index].neighbour_index = container_.size();
  }

  void revert(size_t branch_index) {
    container_.resize(branch_index);
  }

  auto finish() {
    commit(0);
    return stack_tree_container(std::move(container_));
  }

private:
  underlying_type container_;
};


}
}

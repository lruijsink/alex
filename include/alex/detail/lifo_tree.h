#pragma once

#include "./lifo_tree_node.h"

namespace alex {
namespace detail {


template<class ContainerType>
class lifo_tree {
public:
  using node = lifo_tree_node<ContainerType>;

  lifo_tree(ContainerType&& container)
    : container_(std::move(container)) {}

  auto root() const {
    return node(container_, 0);
  }

private:
  ContainerType container_;
};


}
}

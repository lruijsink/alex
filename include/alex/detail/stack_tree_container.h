#pragma once

#include "./stack_tree_node.h"

namespace alex {
namespace detail {


template<class UnderlyingType>
class stack_tree_container {
public:
  using node = stack_tree_node<UnderlyingType>;

  stack_tree_container(UnderlyingType&& underlying)
    : underlying_(std::move(underlying)) {}

  auto root() const {
    return node(underlying_, 0);
  }

private:
  UnderlyingType underlying_;
};


}
}

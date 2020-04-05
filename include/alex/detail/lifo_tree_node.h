#pragma once

#include "./iterator_range.h"
#include "./lifo_tree_iterator.h"

namespace alex {
namespace detail {


template<class ContainerType>
class lifo_tree_node {
public:
  using container_type = ContainerType;
  using range_type = iterator_range<lifo_tree_iterator<lifo_tree_node>,
                                    lifo_tree_sentinel>;

  lifo_tree_node(const container_type& container, size_t index)
    : container_(container)
    , index_(index) {}

  auto token() const {
    return container_[index_].value;
  }

  auto children() const {
    return range_type({container_, index_ + 1},
                      {container_[index_].next_index});
  }

private:
  const container_type& container_;
  size_t index_;
};


}
}

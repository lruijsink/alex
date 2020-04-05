#pragma once

namespace alex {
namespace detail {


template<class ValueType>
struct stack_tree_element {
  ValueType value;
  size_t neighbour_index;
};


}
}

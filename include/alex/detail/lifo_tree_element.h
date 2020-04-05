#pragma once

namespace alex {
namespace detail {


template<class ValueType>
struct lifo_tree_element {
  ValueType value;
  size_t next_index;
};


}
}

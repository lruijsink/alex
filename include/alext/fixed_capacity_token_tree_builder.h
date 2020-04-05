#pragma once

#include "./detail/lifo_tree_fixed_capacity_builder.h"

namespace alex {


template<class T>
using token_tree_fixed_capacity = detail::lifo_tree_fixed_capacity_builder<T>;


}

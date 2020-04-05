#pragma once

#include <memory>

#include "alex/token.h"

#include "./detail/stack_tree_builder_fixed_capacity.h"

namespace alex {


using token_tree_builder_fixed_capacity =
  detail::stack_tree_builder_fixed_capacity<token>;


}

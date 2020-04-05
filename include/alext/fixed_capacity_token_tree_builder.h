#pragma once

#include <memory>

#include "alex/token.h"

#include "./detail/fixed_capacity_lifo_tree_builder.h"

namespace alex {


using fixed_capacity_token_tree_builder =
  detail::fixed_capacity_lifo_tree_builder<token>;


}

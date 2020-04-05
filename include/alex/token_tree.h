#pragma once

#include <vector>

#include "./token.h"
#include "./detail/stack_tree_builder_vector.h"
#include "./detail/stack_tree_container.h"

namespace alex {


using token_tree_builder_vector = detail::stack_tree_builder_vector<token>;
using token_tree_builder = token_tree_builder_vector;
using token_tree = token_tree_builder::finished_type;


}

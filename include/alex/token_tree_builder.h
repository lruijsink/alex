#pragma once

#include "./token.h"
#include "./detail/lifo_tree_builder.h"

namespace alex {


using token_tree_builder = detail::lifo_tree_builder<token>;


}

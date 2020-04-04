#pragma once

#include "token_tree_index.h"

namespace alex {
  namespace detail {
    template<class T>
    struct token_tree_node_data {
      T value;
      token_tree_index end;
    };
  }
}

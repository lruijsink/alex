#pragma once

#include <vector>
#include "token_tree_index.h"
#include "token_tree_node_data.h"

namespace alex {
  namespace detail {
    template<class T>
    class token_tree_container;

    template<class T>
    class token_tree_container<std::vector<token_tree_node_data<T>>> {
      std::vector<token_tree_node_data<T>> container_;

    public:
      const auto& at(token_tree_index index) const {
        return container_.at((size_t) index);
      }
      
      auto& at(token_tree_index index) {
        return container_.at((size_t) index);
      }
      
      auto size() const {
        return container_.size();
      }

      auto push(T value) {
        container_.emplace_back().value = value;
      }

      auto resize(size_t size) const {
        container_.resize(size);
      }
    };
  }
}

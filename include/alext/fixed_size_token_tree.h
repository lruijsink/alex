#pragma once

#include <memory>
#include "alex/token_tree.h"
#include "alex/token_tree_container.h"
#include "alex/token_tree_index.h"
#include "alex/token_tree_node_data.h"

namespace alex {
  namespace detail {
    template<class T, size_t N>
    class basic_fixed_size_token_tree_container {};

    template<class T, size_t N>
    class token_tree_container<basic_fixed_size_token_tree_container<T, N>> {
      std::unique_ptr<token_tree_node_data<T>[]> container_;
      size_t size_;

    public:
      token_tree_container()
        : container_(std::make_unique<token_tree_node_data<T>[]>(N)), size_(0) {
      }
      const auto& at(token_tree_index index) const {
        return container_[(size_t) index];
      }
      
      auto& at(token_tree_index index) {
        return container_[(size_t) index];
      }
      
      auto size() const {
        return size_;
      }

      auto push(T value) {
        container_[size_++].value = value;
      }

      auto resize(size_t size) {
        size_ = size;
      }
    };
  }
  
  template<size_t N> using fixed_size_token_tree
    = detail::basic_token_tree<token, detail::basic_fixed_size_token_tree_container<token, N>>;
}

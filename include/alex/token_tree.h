#pragma once

#include "token.h"
#include "token_tree_container.h"
#include "token_tree_index.h"
#include "token_tree_node_data.h"

namespace alex {
  namespace detail {
    template<class T, class ContainerT = std::vector<token_tree_node_data<T>>>
    class basic_token_tree {
      token_tree_container<ContainerT> container_;

    public:
      class iterator {
        const basic_token_tree& tree_;
        token_tree_index index_;

      public:
        iterator(const basic_token_tree& tree, token_tree_index index)
          : tree_(tree), index_(index) {}

        auto operator++() {
          index_ = tree_.container_.at(index_).end;
        }

        auto operator!=(iterator s) const {
          return index_ != s.index_;
        }

        auto operator*() const {
          return node(tree_, index_);
        }
      };

      class node {
        const basic_token_tree& tree_;
        token_tree_index pos_;

      public:
        node(const basic_token_tree& t, token_tree_index p)
          : tree_(t), pos_(p) {}
        
        auto value() const {
          return tree_.container_.at(pos_).value;
        }

        auto begin() const {
          return iterator(tree_, token_tree_index((size_t) pos_ + 1));
        }

        auto end() const {
          return iterator(tree_, tree_.container_.at(pos_).end);
        }
      };

      auto add(T value) {
        container_.push(value);
        return token_tree_index(container_.size() - 1);
      }

      auto commit(token_tree_index index) {
        container_.at(index).end = token_tree_index(container_.size());
      }

      auto revert(token_tree_index index) {
        container_.resize((size_t) index);
      }

      auto root() const {
        return node(*this, token_tree_index(0));
      }
    };
  }

  using token_tree = detail::basic_token_tree<token>;
}

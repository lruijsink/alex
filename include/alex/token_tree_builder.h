#pragma once

#include <string_view>

#include "./token_root.h"
#include "./token_data.h"

#include "./detail/lifo_tree_builder.h"

namespace alex {


template<class T>
using token_tree_dynamic = detail::lifo_tree_builder<T>;

template<class TokenType,
         template<class> typename UnderlyingType = token_tree_dynamic>
class token_tree_builder {
public:
  using token_type = TokenType;
  using token_data_type = token_data<token_type, std::string_view>;
  using underlying_type = UnderlyingType<token_data_type>;
  using marker_type = typename underlying_type::marker_type;
  using tree_type = typename underlying_type::tree_type;

  template<class... ForwardArgsTS>
  token_tree_builder(ForwardArgsTS&&... args)
    : underlying_(std::forward<ForwardArgsTS>(args)...)
    , root_marker_(underlying_.branch()) {}

  auto branch() -> marker_type {
    return underlying_.branch();
  }

  auto commit(marker_type marker, token_type token, std::string_view content) {
    underlying_.commit(marker, token_data_type(token, content));
  }

  auto revert(marker_type marker) {
    underlying_.revert(marker);
  }

  auto finish() {
    underlying_.commit(root_marker_, token_data_type(token_root<token_type>(), ""));
    return std::move(underlying_.finish());
  }

private:
  underlying_type underlying_;
  marker_type root_marker_;
};


}

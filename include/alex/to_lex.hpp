#pragma once
#include <optional>
#include <string_view>
#include "lexing_context.hpp"

namespace alex {

constexpr auto to_lex(char char_to_match) {
  return [=](lexing_context context) {
    return !context.data().empty() && context.data().front() == char_to_match
               ? std::optional(context.advance(1))
               : std::nullopt;
  };
}

constexpr auto to_lex(std::string_view string_to_match) {
  return [=](lexing_context context) {
    return context.data().substr(0, string_to_match.length()) == string_to_match
               ? std::optional(context.advance(string_to_match.length()))
               : std::nullopt;
  };
}

template <class T>
constexpr auto to_lex(T lex, std::enable_if_t<is_lex<T>, void>* = nullptr) {
  return lex;
}

}  // namespace alex

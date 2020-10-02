#pragma once

#include <optional>
#include <type_traits>

#include <string_view>

namespace alex {

class lexing_context {
 public:
  constexpr lexing_context(std::string_view data) : data_(data) {}

  constexpr auto data() const noexcept { return data_; }
  constexpr auto advance(size_t count) const noexcept {
    return lexing_context(data_.substr(count));
  }

 private:
  std::string_view data_;
};

}  // namespace alex

namespace alex {

template <class T>
constexpr bool is_lex =
    std::is_invocable_r_v<std::optional<lexing_context>, T, lexing_context&>;

}  // namespace alex

#include <optional>
#include <string_view>

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

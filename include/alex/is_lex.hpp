#pragma once
#include "lexing_context.hpp"
#include <optional>
#include <type_traits>

namespace alex {

template <class T>
constexpr bool is_lex =
    std::is_invocable_r_v<std::optional<lexing_context>, T, lexing_context &>;

} // namespace alex

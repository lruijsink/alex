#pragma once
#include <concepts>
#include <optional>
#include <string_view>
namespace alex {

constexpr auto mismatch = std::optional<int>();
constexpr auto match(size_t n) { return std::optional<int>(n); }

template <class T>
concept Lex = std::is_invocable_r_v<std::optional<int>, T, std::string_view>;

//=============================================================================
// Basic
//=============================================================================

constexpr auto alwaysMatch = [](std::string_view) { return match(0); };

constexpr auto neverMatch = [](std::string_view) { return mismatch; };

constexpr auto any = [](std::string_view text) {
  return text.empty() ? mismatch : match(1);
};

constexpr auto textEnd = [](std::string_view text) {
  return text.empty() ? match(0) : mismatch;
};

//=============================================================================
// Parametrized
//=============================================================================

constexpr auto range(char from, char to) {
  return [=](std::string_view text) {
    if (text.empty()) return mismatch;
    return (text.front() >= from && text.front() <= to) ? match(1) : mismatch;
  };
}

constexpr auto noneOf(char c) {
  return [=](std::string_view text) {
    return text.starts_with(c) ? mismatch : match(1);
  };
}

constexpr auto literal(char c) {
  return [=](std::string_view text) {
    return text.starts_with(c) ? match(1) : mismatch;
  };
}

constexpr auto literal(std::string_view sv) {
  return [=](std::string_view text) {
    return text.starts_with(sv) ? match(sv.size()) : mismatch;
  };
}

constexpr auto lexify(char c) { return literal(c); }
constexpr auto lexify(std::string_view s) { return literal(s); }
constexpr auto lexify(Lex auto l) { return l; }

template <class T>
concept Lexifiable = Lex<T> || Lex<decltype(lexify(std::declval<T>()))>;

//=============================================================================
// Modifiers
//=============================================================================

constexpr auto optional(Lexifiable auto expr) {
  auto lex = lexify(expr);
  return [=](std::string_view text) { return match(lex(text).value_or(0)); };
}

//=============================================================================
// Combinators
//=============================================================================

constexpr auto operator+(Lexifiable auto expr1, Lexifiable auto expr2) {
  auto lex1 = lexify(expr1);
  auto lex2 = lexify(expr2);
  return [=](std::string_view text) {
    auto res1 = lex1(text);
    if (!res1) return mismatch;
    auto res2 = lex2(text.substr(*res1));
    return res2 ? (*res1 + *res2) : mismatch;
  };
}

constexpr auto operator|(Lexifiable auto expr1, Lexifiable auto expr2) {
  auto lex1 = lexify(expr1);
  auto lex2 = lexify(expr2);
  return [=](std::string_view text) {
    auto res = lex1(text);
    return res ? res : lex2(text);
  };
}

constexpr auto sequence(Lexifiable auto... exprs) {
  return (lexify(exprs) + ... + alwaysMatch);
}

constexpr auto choice(Lexifiable auto... exprs) {
  return (lexify(exprs) | ... | neverMatch);
}

//=============================================================================
// Repeaters
//=============================================================================

constexpr auto repeat(Lexifiable auto expr) {
  auto lex = lexify(expr);
  return [=](std::string_view text) {
    auto it = text.begin();
    auto res = mismatch;
    while ((res = lex(it))) it += *res;
    return match(it - text.begin());
  };
}

constexpr auto repeat(Lexifiable auto val, Lexifiable auto sep) {
  auto vLex = lexify(val);
  auto sLex = lexify(sep);
  return [=](std::string_view text) {
    auto res = vLex(text);
    return match(res ? *res + *repeat(sLex + vLex)(text.substr(*res)) : 0);
  };
}

//=============================================================================
// Recursive
//=============================================================================

class recursive {
  bool clone_;

  struct store {
    struct base {
      constexpr virtual std::optional<int> invoke(std::string_view) const = 0;
    } * pBase;

    template <Lex T>
    struct impl : base {
      T lex_;
      constexpr impl(T lex) : lex_(lex) {}
      constexpr std::optional<int> invoke(
          std::string_view text) const override {
        return lex_(text);
      }
    };
  } * pStore_;

 public:
  constexpr recursive() : clone_(false), pStore_(new store()) {}
  constexpr recursive(const recursive& r) : clone_(true), pStore_(r.pStore_) {}
  constexpr ~recursive() {
    if (!clone_) {
      delete pStore_->pBase;
      delete pStore_;
    }
  }

  constexpr void operator=(Lexifiable auto lex) {
    pStore_->pBase = new store::impl(lexify(lex));
  }

  constexpr std::optional<int> operator()(std::string_view text) const {
    return pStore_->pBase->invoke(text);
  }
};

}  // namespace alex

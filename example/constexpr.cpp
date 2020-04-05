struct reader {
  constexpr reader(const char* s) : itr_(s) {}
  constexpr auto operator*() const { return *itr_; }
  constexpr operator bool() const { return *itr_ != 0; }
  constexpr auto& operator++() { ++itr_; return *this; }
private:
  const char* itr_;
};

struct lex_result {
  constexpr lex_result(reader r) : r_(r), t_(true) {}
  constexpr lex_result() : r_(nullptr), t_(false) {}
  constexpr auto value() const { return r_; }
  constexpr auto value_or(reader r) const { return t_ ? r_ : r; }
  constexpr operator bool() const { return t_; }
private:
  bool t_;
  reader r_;
};

constexpr lex_result lex_no_match;

constexpr auto false_lex = [](reader) {
  return lex_no_match;
};

constexpr auto true_lex = [](reader r) {
  return lex_result(r);
};

constexpr auto any = [](reader r) {
  return r ? lex_result(++r) : lex_no_match;
};

constexpr auto eof = [](reader r) {
  return r ? lex_no_match : lex_result(r);
};

constexpr auto any_but = [](char c) {
  return [=](reader r) -> lex_result {
    return (r && *r != c) ? lex_result(++r) : lex_no_match;
  };
};

constexpr auto from_to = [](char from, char to) {
  return [=](reader r) -> lex_result {
    return (r && from <= *r && *r <= to) ? lex_result(++r) : lex_no_match;
  };
};

template<class T>
constexpr auto make_lex(T l) noexcept {
  return l;
}

constexpr auto make_lex(char c) noexcept {
  return [=](reader r) -> lex_result {
    return (r && *r == c) ? lex_result(++r) : lex_no_match;
  };
}

constexpr auto make_lex(const char* s) noexcept {
  return [=] (reader r) -> lex_result {
    auto p = s;
    while (*p != 0) {
      if (!r || *r != *(p++)) return lex_no_match;
      ++r;
    }
    return r;
  };
};

constexpr auto optional = [](auto l) {
  auto L = make_lex(l);
  return [=](reader r) -> lex_result {
    return L(r).value_or(r);
  };
};

constexpr auto one_of() {
  return false_lex;
};

template<class T, class... TS>
constexpr auto one_of(T l, TS... ls) {
  auto L = make_lex(l);
  return [=](reader r) -> lex_result {
    auto o = L(r);
    return o ? o : one_of(ls...)(r);
  };
};

template<class LhsT, class RhsT>
constexpr auto operator|(LhsT lhs, RhsT rhs) {
  return one_of(lhs, rhs);
}

constexpr auto seq() {
  return true_lex;
}

template<class T, class... TS>
constexpr auto seq(T l, TS... ls) {
  auto L = make_lex(l);
  return [=](reader r) -> lex_result {
    auto o = L(r);
    return o ? seq(ls...)(o.value()) : lex_no_match;
  };
};

template<class LhsT, class RhsT>
constexpr auto operator+(LhsT lhs, RhsT rhs) {
  return seq(lhs, rhs);
}

constexpr auto repeat_min = [] (auto l, int n) {
  auto L = make_lex(l);
  return [=] (reader r) -> lex_result {
    int c = 0;
    while (true) {
      auto o = L(r);
      if (!o) return c >= n ? lex_result(r) : lex_no_match;
      r = o.value();
      c++;
    }
  };
};

constexpr auto repeat = [] (auto l) {
  return repeat_min(l, 0);
};

constexpr auto repeat_sep_min = [] (auto l, auto s, int n) {
  return l + repeat_min(seq(s, l), n - 1);
};

constexpr auto repeat_sep = [] (auto l, auto s) {
  return optional(l) + repeat(seq(s, l));
};

using recursive = lex_result(*)(reader);

constexpr lex_result expr(reader r);

constexpr auto ws = repeat(one_of(' ', '\t', '\r', '\n'));
constexpr auto op = [] (auto l) { return ws + l + ws; };

constexpr auto string_v  = '"' + repeat(('\\' + any) | any_but('"')) + '"';
constexpr auto keyword_v = one_of("null", "true", "false");
constexpr auto object_v  = op('{') + repeat_sep(string_v + ':' + expr, op(',')) + op('}');
constexpr auto array_v   = op('[') + repeat_sep(expr, op(',')) + op(']');
constexpr auto number_v  = optional('-')
+ ('0' | from_to('1', '9')) + repeat(from_to('0', '9'))
+ optional('.' + repeat_min(from_to('0', '9'), 1))
+ optional(one_of('e', 'E') + optional(one_of('-', '+')) + repeat_min(from_to('0', '9'), 1));

constexpr lex_result expr(reader r) {
  return (ws + (string_v | keyword_v | object_v | array_v | number_v) + ws)(r);
}

int main(int, char** argv) {
  constexpr auto lex = expr + eof;
  constexpr auto res = lex(R""""(
    {
      "some": "pretty",
      "com": [ "plicated" ],
      "js": 0, "n": 0, "bj": "ect",
      "with": [
        "nesting",
        [
          "and",
          "everything"
        ],
        -0.1234E+10
      ]
    }
  )"""");
  return lex(argv[0]) ? 1 : 2;
}

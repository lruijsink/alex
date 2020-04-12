#include <string_view>
#include <optional>

namespace alex {

using parsing_iterator = const char*;
using parsing_result = parsing_iterator;
using input_text = std::string_view;

class parsing_context {
public:
  constexpr parsing_context(input_text input)
    : input_(input) {
  }

  constexpr const auto input_remaining_after(parsing_iterator itr) {
    return input_.length() - (itr - input_.data());
  }

private:
  input_text input_;
};

constexpr auto continue_at(parsing_iterator itr) {
  return parsing_result(itr);
}

constexpr auto result_to_iterator(parsing_result result) {
  return parsing_iterator(result);
}

constexpr auto mismatch = parsing_result(nullptr);

constexpr auto empty_match = [] (parsing_iterator itr,
                                 parsing_context& context) {
  return continue_at(itr);
};

constexpr auto empty_mismatch = [] (parsing_iterator itr,
                                    parsing_context& context) {
  return mismatch;
};

constexpr auto any_char = [] (parsing_iterator itr,
                              parsing_context& context) {
  return context.input_remaining_after(itr) != 0
    ? continue_at(itr + 1)
    : mismatch;
};

constexpr auto end_of_input = [] (parsing_iterator itr,
                                  parsing_context& context) {
  return context.input_remaining_after(itr) == 0
    ? continue_at(itr)
    : mismatch;
};

constexpr auto char_range = [] (char from, char to) {
  return [=] (parsing_iterator itr, parsing_context& context) {
    return context.input_remaining_after(itr) != 0 &&
      from <= *itr && *itr <= to
      ? continue_at(itr + 1)
      : mismatch;
  };
};

template<class T>
constexpr auto lexify(T lambda_lex) {
  return lambda_lex;
}

constexpr auto lexify(char char_to_match) {
  return [=] (parsing_iterator itr, parsing_context& context) {
    return context.input_remaining_after(itr) != 0 &&
      *itr == char_to_match
      ? continue_at(itr + 1)
      : mismatch;
  };
};

constexpr auto lexify(std::string_view string_to_match) {
  return [=] (parsing_iterator itr, parsing_context& context) {
    if (context.input_remaining_after(itr) < string_to_match.length())
      return mismatch;

    for (auto c : string_to_match)
      if (*(itr++) != c)
        return mismatch;

    return continue_at(itr);
  };
};

constexpr auto lexify(const char* string_to_match) {
  return lexify(std::string_view(string_to_match));
}

constexpr auto optional = [] (auto underlying_lex) {
  auto L = lexify(underlying_lex);
  return [=] (parsing_iterator itr, parsing_context& context) {
    auto result = L(itr, context);
    return result == mismatch
      ? continue_at(itr)
      : result_to_iterator(result);
  };
};

constexpr auto except_if = [] (auto matching_lex, auto excluding_lex) {
  auto M = lexify(matching_lex);
  auto E = lexify(excluding_lex);
  return [=] (parsing_iterator itr, parsing_context& context) {
    return E(itr, context) == mismatch
      ? M(itr, context)
      : mismatch;
  };
};

constexpr auto any_char_but = [] (char c) {
  return except_if(any_char, c);
};

template<class Lex1, class Lex2>
constexpr auto operator|(Lex1 lex1, Lex2 lex2) {
  auto L1 = lexify(lex1);
  auto L2 = lexify(lex2);
  return [=] (parsing_iterator itr, parsing_context& context) {
    auto first_result = L1(itr, context);
    return first_result != mismatch
      ? first_result
      : L2(itr, context);
  };
}

constexpr auto choice = [] (auto... lexes) {
  return (lexes | ... | empty_mismatch);
};

template<class Lex1, class Lex2>
constexpr auto operator+(Lex1 lex1, Lex2 lex2) {
  auto L1 = lexify(lex1);
  auto L2 = lexify(lex2);
  return [=] (parsing_iterator itr, parsing_context& context) {
    auto first_result = L1(itr, context);
    return first_result != mismatch
      ? L2(result_to_iterator(first_result), context)
      : mismatch;
  };
}

constexpr auto sequence = [] (auto... lexes) {
  return (lexes + ... + empty_match);
};

constexpr auto repeat = [] (auto lex) {
  auto L = lexify(lex);
  return [=] (parsing_iterator itr, parsing_context& context) {
    parsing_result result;
    while ((result = L(itr, context)) != mismatch) {
      itr = result_to_iterator(result);
    }
    return continue_at(itr);
  };
};

constexpr auto repeat_n = [] (int count, auto lex) {
  auto L = lexify(lex);
  return [=] (parsing_iterator itr, parsing_context& context) {
    for (int i = 0; i < count; i++) {
      auto result = L(itr, context);
      if (result == mismatch)
        return mismatch;
      itr = result_to_iterator(result);
    }
    return continue_at(itr);
  };
};

constexpr auto repeat_min_n = [] (int min_count, auto lex) {
  auto L = lexify(lex);
  return repeat_n(min_count, L) + repeat(L);
};

constexpr auto repeat_min_1 = [] (auto lex) {
  auto L = lexify(lex);
  return L + repeat(L);
};

constexpr auto repeat_separated = [] (auto lex, auto separator_lex) {
  auto L = lexify(lex);
  auto S = lexify(separator_lex);
  return optional(L + repeat(S + L));
};

constexpr auto repeat_n_separated = [] (int count, auto lex, auto separator_lex) {
  auto L = lexify(lex);
  auto S = lexify(separator_lex);
  return L + repeat_n(count - 1, S + L);
};

constexpr auto repeat_min_n_separated = [] (int count, auto lex, auto separator_lex) {
  auto L = lexify(lex);
  auto S = lexify(separator_lex);
  return repeat_n_separated(count, L, S) + repeat(S + L);
};

constexpr auto repeat_min_1_separated = [] (auto lex, auto separator_lex) {
  auto L = lexify(lex);
  auto S = lexify(separator_lex);
  return L + repeat(S + L);
};

}

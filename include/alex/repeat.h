#pragma once

#include "defines.h"
#include "grammar.h"
#include "fixed.h"

ALEX_NAMESPACE_BEGIN


namespace tag
{
  struct repeat {};
}

template<class PatternT, class UntilT, class SeparatorT>
class grammar<tag::repeat, PatternT, UntilT, SeparatorT>
{
public:
  static constexpr bool has_empty_until
    = std::is_same_v<UntilT, grammar<std::false_type>>;
  
  static constexpr bool has_empty_separator
    = std::is_same_v<SeparatorT, grammar<std::true_type>>;

  static constexpr int no_min = 0;
  static constexpr int no_max = -1;

  grammar(PatternT pattern)
    : pattern_(pattern)
    , min_(no_min)
    , max_(no_max)
  {
  }

  grammar(PatternT pattern,
          UntilT until,
          SeparatorT separator,
          int min_v,
          int max_v)
    : pattern_(pattern)
    , until_(until)
    , separator_(separator)
    , min_(min_v)
    , max_(max_v)
  {
  }

  template<class... TS>
  bool match(reader<TS...> r)
  {
    if (max_ != no_max && max_ < min_)
      return false;

    int count = 0;

    auto P = pattern_;
    auto U = until_;
    auto S = separator_;

    if (has_empty_until)
    {
      while (count == 0 ? r.parse(P) : r.parse(S + P))
      {
        ++count;
        if (max_ != no_max && count == max_)
          return true;
      }
    }
    else
    {
      while (!r.parse(U))
      {
        if (max_ != no_max && count == max_)
          return false;
        else if (count == 0 ? r.parse(P) : r.parse(S + P))
          ++count;
        else
          return false;
      }
    }
    return min_ <= count;
  }

  auto min(int n)
  {
    if (n >= 0)
      min_ = n;
    return *this;
  }

  auto max(int n)
  {
    if (n >= 0)
      max_ = n;
    return *this;
  }

  auto count(int n)
  {
    min_ = n;
    max_ = n;
    return *this;
  }

  template<class... TS>
  auto until(grammar<TS...> g)
  {
    using new_type = grammar<tag::repeat, PatternT, grammar<TS...>, SeparatorT>;
    return new_type(pattern_, g, separator_, min_, max_);
  }

  template<class T>
  auto until(T v)
  {
    return until(grammar<T>(v));
  }

  template<class... TS>
  auto separator(grammar<TS...> g)
  {
    using new_type = grammar<tag::repeat, PatternT, UntilT, grammar<TS...>>;
    return new_type(pattern_, until_, g, min_, max_);
  }

  template<class T>
  auto separator(T v)
  {
    return separator(grammar<T>(v));
  }

private:
  int min_;
  int max_;

  PatternT pattern_;
  UntilT until_;
  SeparatorT separator_;
};

template<class T>
auto repeat(T g)
{
  using basic_type = grammar<
    tag::repeat,
    decltype(grammar(g)),
    grammar<std::false_type>,
    grammar<std::true_type>
  >;
  return basic_type(grammar(g));
}


ALEX_NAMESPACE_END

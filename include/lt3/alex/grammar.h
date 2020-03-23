#pragma once

#include <type_traits>
#include "defines.h"
#include "tag.h"
#include "reader.h"
#include "reader_abstract.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class T>
class grammar<T>
{
public:
  grammar(T fnc) : fnc_(fnc) {}

  template<class... TS>
  bool match(reader<TS...> r) const
  {
    return fnc_(r);
  }

private:
  static constexpr bool is_fnc =
    std::is_invocable_v<T, reader<tag::poly>>;

  std::enable_if_t<is_fnc, T> fnc_;
};

template<class L, class R>
auto operator+(L lhs, R rhs)
{
  return grammar([=] (auto r) {
    return grammar(lhs).match(r) && grammar(rhs).match(r);
  });
}

template<class L, class R>
auto operator||(L lhs, R rhs)
{
  return grammar([=] (auto r) {
    return grammar(lhs).match(r) || grammar(rhs).match(r);
  });
}

template<class T>
auto operator||(bool, grammar<T>) = delete;

template<class T>
auto operator||(grammar<T>, bool) = delete;

template<class T>
auto operator+(bool, grammar<T>) = delete;

template<class T>
auto operator+(grammar<T>, bool) = delete;


LT3_ALEX_NAMESPACE_END

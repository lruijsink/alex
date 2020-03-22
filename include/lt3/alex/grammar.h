#pragma once

#include <functional>
#include "defines.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class DelegateT>
class grammar
{
public:
  using delegate_type = DelegateT;

  grammar(delegate_type d)
    : delegate_(d)
  {
  }

  template<class T>
  bool match(T& parser) const
  {
    return std::function<bool(T&)>(delegate_)(parser);
  }

private:
  delegate_type delegate_;
};

template<class L, class R>
auto operator||(grammar<L> lhs, grammar<R> rhs)
{
  return grammar([=] (auto& parser) {
    return parser.parse(lhs) || parser.parse(rhs);
  });
}

template<class L, class R>
auto operator+(grammar<L> lhs, grammar<R> rhs)
{
  return grammar([=] (auto& parser) {
    return parser.parse(lhs) && parser.parse(rhs);
  });
}

template<class T, class G>
auto operator||(grammar<G> g, T v)
{
  return g || grammar(v);
}

template<class T, class G>
auto operator||(T v, grammar<G> g)
{
  return grammar(v) || g;
}

template<class T, class G>
auto operator+(grammar<G> g, T v)
{
  return g + grammar(v);
}

template<class T, class G>
auto operator+(T v, grammar<G> g)
{
  return grammar(v) + g;
}

template<class G>
auto operator||(bool, grammar<G>) = delete;

template<class G>
auto operator||(grammar<G>, bool) = delete;

template<class G>
auto operator+(bool, grammar<G>) = delete;

template<class G>
auto operator+(grammar<G>, bool) = delete;


LT3_ALEX_NAMESPACE_END

#pragma once

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

  template<class ParserT>
  bool match(ParserT& parser) const
  {
    return delegate_(parser);
  }

private:
  delegate_type delegate_;
};

template<class L, class R>
auto operator||(L lhs, R rhs)
{
  return grammar([=] (auto& parser) {
    return parser.parse(lhs) || parser.parse(rhs);
  });
}

template<class L, class R>
auto operator+(L lhs, R rhs)
{
  return grammar([=] (auto& parser) {
    return parser.parse(lhs) && parser.parse(rhs);
  });
}


LT3_ALEX_NAMESPACE_END

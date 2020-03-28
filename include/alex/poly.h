#pragma once

#include <functional>
#include "defines.h"

namespace ALEX_NAMESPACE_NAME
{


namespace detail
{
  namespace tag
  {
    struct poly {};
  }
}

template<>
class grammar<detail::tag::poly>
{
public:
  grammar()
    : f_([=] (reader& r) { return false; })
  {
  }

  template<class... TS>
  grammar(grammar<TS...> g)
    : f_([=] (reader& r) { return g.read_and_test(r); })
  {
  }

  bool read_and_test(reader& r) const
  {
    return f_(r);
  }

private:
  std::function<bool(reader& r)> f_;
};

template<class T>
auto poly(T g)
{
  return grammar<detail::tag::poly>(g);
}


}

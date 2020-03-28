#pragma once

#include <string>
#include "defines.h"
#include "grammar.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


namespace detail
{
  namespace tag
  {
    struct symbol {};
  }
}

template<class... TS>
class grammar<detail::tag::symbol, grammar<TS...>>
{
public:
  grammar(std::string name, grammar<TS...> g)
    : name_(name)
    , g_(g)
  {
  }

  template<class... C_TS>
  auto operator=(grammar<C_TS...> g)
  {
    g_ = g;
  }

  bool read_and_test(reader& r) const
  {
    auto begin = r.pos();
    auto& symb = r.begin_symbol(name_);
    if (r.match(g_))
    {
      r.commit_symbol();
      symb.set_content(r.view(begin, r.pos()));
      return true;
    }
    else
    {
      r.discard_symbol();
      return false;
    }
  }

private:
  std::string name_;
  grammar<TS...> g_;
};

template<class T>
auto symbol(std::string name, T g)
{
  return grammar<detail::tag::symbol, decltype(grammar(g))>(name, grammar(g));
}


}

#pragma once

#include "defines.h"

namespace ALEX_NAMESPACE_NAME {


struct symbol_tag {};

template<class... TS>
class grammar<symbol_tag, grammar<TS...>>
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

  template<class... R_TS>
  bool read_and_test(reader<R_TS...> r)
  {
    r.begin_symbol(name_);
    if (r.parse(g_))
    {
      r.commit_symbol();
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
  return grammar<symbol_tag, decltype(grammar(g))>(name, grammar(g));
}


}

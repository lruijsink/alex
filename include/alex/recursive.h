#pragma once

#include <memory>
#include "defines.h"
#include "grammar_abstract.h"
#include "tag.h"

ALEX_NAMESPACE_BEGIN


//
// R ---> shared_ptr ---> grammar<tag::poly> ---> nullptr
//

// R ---
//      \
//       +---> shared_ptr ---> grammar<tag::poly> ---> grammar<TS...>
//      /
// R'---

template<>
class grammar<tag::recursive>
{
public:
  grammar()
    : ptr_(std::make_shared<grammar<tag::poly>>())
  {
  }

  grammar(const grammar& g)
    : ptr_(g.ptr_)
  {
  }

  template<class... TS>
  grammar(grammar<TS...> g) = delete;

  template<class... TS>
  auto& operator=(grammar<TS...> g)
  {
    *ptr_ = g;
    return *this;
  }

  template<class... TS>
  bool match(reader<TS...> r)
  {
    return ptr_->match(r);
  }

private:
  std::shared_ptr<grammar<tag::poly>> ptr_;
};

inline auto recursive()
{
  return grammar<tag::recursive>();
}


ALEX_NAMESPACE_END

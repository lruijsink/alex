#pragma once

#include <memory>
#include "defines.h"
#include "grammar.h"
#include "grammar_abstract.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


namespace detail
{
  namespace tag
  {
    struct recursive {};
  }
}

template<>
class grammar<detail::tag::recursive>
{
public:
  grammar()
    : ptr_(std::make_shared<grammar<detail::tag::poly>>())
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

  bool read_and_test(reader& r)
  {
    return ptr_->read_and_test(r);
  }

private:
  std::shared_ptr<grammar<detail::tag::poly>> ptr_;
};

inline auto recursive()
{
  return grammar<detail::tag::recursive>();
}


}

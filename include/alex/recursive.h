#pragma once

#include <memory>
#include "defines.h"
#include "grammar_abstract.h"
#include "tag.h"

namespace ALEX_NAMESPACE_NAME {


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

  bool read_and_test(reader& r)
  {
    return ptr_->read_and_test(r);
  }

private:
  std::shared_ptr<grammar<tag::poly>> ptr_;
};

inline auto recursive()
{
  return grammar<tag::recursive>();
}


}

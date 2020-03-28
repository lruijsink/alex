#pragma once

#include <memory>
#include "defines.h"
#include "grammar.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


namespace detail
{
  namespace tag
  {
    struct poly {};
  }

  struct grammar_abstract
  {
    virtual ~grammar_abstract()
    {
    }

    virtual bool read_and_test(::ALEX_NAMESPACE_NAME::reader&) = 0;
    virtual std::unique_ptr<grammar_abstract> clone() const = 0;
  };

  template<class... TS>
  class grammar_impl : public grammar_abstract
  {
  public:
    grammar_impl(::ALEX_NAMESPACE_NAME::grammar<TS...> g) : g_(g) {}

    bool read_and_test(::ALEX_NAMESPACE_NAME::reader& r) override
    {
      return g_.read_and_test(r);
    }

    std::unique_ptr<grammar_abstract> clone() const override
    {
      return std::make_unique<grammar_impl>(g_);
    }

  private:
    ::ALEX_NAMESPACE_NAME::grammar<TS...> g_;
  };
}

template<>
class grammar<detail::tag::poly>
{
public:
  grammar()
    : ptr_(nullptr) {}

  grammar(const grammar<detail::tag::poly>& g)
    : ptr_(g.ptr_->clone()) {}

  grammar(const detail::grammar_abstract& g)
    : ptr_(g.clone()) {}

  template<class... TS>
  grammar(detail::grammar_impl<TS...> g)
    : ptr_(g.clone()) {}

  template<class... TS>
  grammar(grammar<TS...> g)
    : ptr_(new detail::grammar_impl<TS...>(g)) {}

  template<class... TS>
  grammar(TS... vs)
    : grammar(grammar<TS...>(vs...)) {}

  template<class... TS>
  auto& operator=(const grammar<TS...>& g)
  {
    ptr_ = std::make_unique<detail::grammar_impl<TS...>>(g);
    return* this;
  }

  template<class... TS>
  auto& operator=(grammar<TS...>&& g)
  {
    ptr_ = std::make_unique<detail::grammar_impl<TS...>>(g);
    return* this;
  }

  template<class... TS>
  auto& operator=(const grammar<detail::tag::poly>& g)
  {
    ptr_ = g.ptr_->clone();
    return* this;
  }

  template<class... TS>
  auto& operator=(grammar<detail::tag::poly>&& g)
  {
    ptr_ = std::move(g.ptr_);
    return* this;
  }

  bool read_and_test(reader& r)
  {
    return ptr_->read_and_test(r);
  }

private:
  std::unique_ptr<detail::grammar_abstract> ptr_;
};



}

#pragma once

#include "defines.h"
#include "tag.h"
#include "grammar.h"
#include "reader_abstract.h"

ALEX_NAMESPACE_BEGIN


struct grammar_abstract
{
  virtual ~grammar_abstract()
  {
  }

  virtual bool read_and_test(const reader<tag::poly>&) = 0;
  virtual std::unique_ptr<grammar_abstract> clone() const = 0;
};

template<class... TS>
class grammar_impl : public grammar_abstract
{
public:
  grammar_impl(grammar<TS...> g) : g_(g) {}

  bool read_and_test(const reader<tag::poly>& r) override
  {
    return g_.read_and_test(r);
  }

  std::unique_ptr<grammar_abstract> clone() const override
  {
    return std::make_unique<grammar_impl>(g_);
  }

private:
  grammar<TS...> g_;
};

template<>
class grammar<tag::poly>
{
public:
  grammar()
    : ptr_(nullptr) {}

  grammar(const grammar<tag::poly>& g)
    : ptr_(g.ptr_->clone()) {}

  grammar(const grammar_abstract& g)
    : ptr_(g.clone()) {}

  template<class... TS>
  grammar(grammar_impl<TS...> g)
    : ptr_(g.clone()) {}

  template<class... TS>
  grammar(grammar<TS...> g)
    : ptr_(new grammar_impl<TS...>(g)) {}

  template<class... TS>
  grammar(TS... vs)
    : grammar(grammar<TS...>(vs...)) {}

  template<class... TS>
  auto& operator=(const grammar<TS...>& g)
  {
    ptr_ = std::make_unique<grammar_impl<TS...>>(g);
    return* this;
  }

  template<class... TS>
  auto& operator=(grammar<TS...>&& g)
  {
    ptr_ = std::make_unique<grammar_impl<TS...>>(g);
    return* this;
  }

  template<class... TS>
  auto& operator=(const grammar<tag::poly>& g)
  {
    ptr_ = g.ptr_->clone();
    return* this;
  }

  template<class... TS>
  auto& operator=(grammar<tag::poly>&& g)
  {
    ptr_ = std::move(g.ptr_);
    return* this;
  }

  template<class... TS>
  bool read_and_test(reader<TS...> r)
  {
    return ptr_->read_and_test(r);
  }

private:
  std::unique_ptr<grammar_abstract> ptr_;
};



ALEX_NAMESPACE_END

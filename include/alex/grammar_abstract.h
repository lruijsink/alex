#pragma once

#include "defines.h"
#include "tag.h"
#include "grammar.h"
#include "reader_abstract.h"

ALEX_NAMESPACE_BEGIN


struct grammar_abstract
{
  virtual bool match(reader<tag::poly>&) = 0;
  virtual std::unique_ptr<grammar_abstract> clone() const = 0;
};

template<class... TS>
class grammar_impl : public grammar_abstract
{
public:
  grammar_impl(grammar<TS...> g) : g_(g) {}

  bool match(reader<tag::poly>& r) override
  {
    return g_.match(r);
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
  grammar(const grammar<tag::poly>& g)
    : ptr_(g.ptr_->clone()) {}

  template<class... TS>
  grammar(grammar<TS...> g)
    : ptr_(new grammar_impl<TS...>(g)) {}

  template<class... TS>
  grammar(TS... vs)
    : grammar(grammar<TS...>(vs...)) {}

  bool match(reader<tag::poly>& r)
  {
    return ptr_->match(r);
  }

private:
  std::unique_ptr<grammar_abstract> ptr_;
};



ALEX_NAMESPACE_END

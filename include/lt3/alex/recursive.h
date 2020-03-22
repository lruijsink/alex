#pragma once

#include <memory>
#include "defines.h"
#include "adapter.h"
//#include "grammar_adapter.h"

LT3_ALEX_NAMESPACE_BEGIN


class recursive
{
public:
  inline recursive()
    : impl_(nullptr)
  {
  }

  template<class GrammarT>
  recursive(GrammarT g)
  {
    impl_ = std::make_shared<grammar_adapter_impl<GrammarT>>(g);
  }

  template<class T>
  bool match(T& parser) const
  {
    return impl_ == nullptr ? false : impl_->match(parser);
  }

private:
  std::shared_ptr<grammar_adapter> impl_;
};

template<>
class grammar<recursive>
{
public:
  grammar(recursive r)
    : r_(r)
  {
  }

  template<class ParserT>
  bool match(ParserT& parser) const
  {
    return r_.match(parser);
  }

private:
  recursive r_;
};


LT3_ALEX_NAMESPACE_END

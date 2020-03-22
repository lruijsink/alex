#pragma once

#include "defines.h"
#include "adapter_traits.h"
#include "parser_adapter.h"

LT3_ALEX_NAMESPACE_BEGIN


class grammar_adapter
{
public:
  virtual bool match(parser_adapter&) = 0;
};

template<class GrammarT>
class grammar_adapter_impl : public grammar_adapter
{
public:
  grammar_adapter_impl(GrammarT grammar)
    : grammar_(grammar)
  {
  }

  bool match(parser_adapter& p) override
  {
    return grammar_.match(p);
  }

private:
  GrammarT grammar_;
};


LT3_ALEX_NAMESPACE_END

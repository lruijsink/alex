#pragma once

#include "defines.h"
#include "adapter_traits.h"
#include "parser_adapter.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class AdapterTraitsT>
class basic_grammar_adapter
{
public:
  using adapter_traits = AdapterTraitsT;

  virtual bool match(basic_parser_adapter<adapter_traits>&) = 0;
};

template<class AdapterTraitsT, class GrammarT>
class basic_grammar_adapter_impl : public basic_grammar_adapter<AdapterTraitsT>
{
public:
  using adapter_traits = AdapterTraitsT;

  basic_grammar_adapter_impl(GrammarT grammar)
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

using grammar_adapter = basic_grammar_adapter<default_adapter_traits>;

template<class GrammarT>
using grammar_adapter_impl = basic_grammar_adapter_impl<default_adapter_traits, GrammarT>;


LT3_ALEX_NAMESPACE_END

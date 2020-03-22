#pragma once

#include "defines.h"
#include "adapter_traits.h"
#include "stream_adapter.h"
#include "grammar_adapter.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class AdapterTraitsT>
class basic_parser_adapter
{
public:
  using adapter_traits = AdapterTraitsT;

  virtual bool parse(const basic_grammar_adapter<adapter_traits>&) = 0;
  virtual basic_stream_adapter<adapter_traits>& stream() = 0;

  template<class GrammarT>
  bool parse(GrammarT g)
  {
    return parse(basic_grammar_adapter_impl<adapter_traits, GrammarT>(g));
  }
};

template<class AdapterTraitsT, class ParserT>
class basic_parser_adapter_impl : public basic_parser_adapter<AdapterTraitsT>
{
public:
  using adapter_traits = AdapterTraitsT;

  basic_parser_adapter_impl(ParserT& parser)
    : parser_(parser)
  {
  }

  bool parse(const basic_grammar_adapter<adapter_traits>& g) override
  {
    return parser_.parser(g);
  }

private:
  ParserT& parser_;
};

using parser_adapter = basic_parser_adapter<default_adapter_traits>;

template<class ParserT>
using parser_adapter_impl = basic_parser_adapter_impl<default_adapter_traits, ParserT>;


LT3_ALEX_NAMESPACE_END

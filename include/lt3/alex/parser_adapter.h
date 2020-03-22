#pragma once

#include "defines.h"
#include "adapter_traits.h"
#include "stream_adapter.h"
#include "grammar_adapter.h"

LT3_ALEX_NAMESPACE_BEGIN


class parser_adapter
{
public:
  virtual bool parse(const grammar_adapter&) = 0;
  virtual stream_adapter& stream() = 0;

  template<class T>
  bool parse(grammar<T> g)
  {
    return parse(grammar_adapter_impl<grammar<T>>(g));
  }
};

template<class ParserT>
class parser_adapter_impl : public parser_adapter
{
public:
  parser_adapter_impl(ParserT& parser)
    : parser_(parser)
  {
  }

  bool parse(grammar_adapter& g) override
  {
    return parser_.parse(g);
  }

  virtual stream_adapter& stream() override
  {
    return stream_adapter_impl(parser_.stream());
  }

private:
  ParserT& parser_;
};


LT3_ALEX_NAMESPACE_END

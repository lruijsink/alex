#pragma once

#include <string>
#include "defines.h"
#include "grammar.h"

LT3_ALEX_NAMESPACE_BEGIN


template<>
class grammar<char>
{
public:
  grammar(char c)
    : c_(c)
  {
  }

  template<class ParserT>
  bool match(ParserT& parser) const
  {
    return parser.stream().get() == c_;
  }

private:
  char c_;
};

template<>
class grammar<std::string>
{
public:
  grammar(std::string s)
    : s_(s)
  {
  }

  template<class ParserT>
  bool match(ParserT& parser) const
  {
    for (auto c : s_)
      if (parser.stream().get() != c)
        return false;
    return true;
  }

private:
  std::string s_;
};

template<>
class grammar<const char*>
{
public:
  grammar(const char* s)
    : s_(s)
  {
  }

  template<class ParserT>
  bool match(ParserT& parser) const
  {
    for (auto c : s_)
      if (parser.stream().get() != c)
        return false;
    return true;
  }

private:
  std::string s_;
};


LT3_ALEX_NAMESPACE_END

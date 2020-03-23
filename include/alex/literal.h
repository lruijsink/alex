#pragma once

#include <string>
#include "defines.h"
#include "grammar.h"
#include "reader.h"

ALEX_NAMESPACE_BEGIN


template<>
class grammar<char>
{
public:
  grammar(char c) : c_(c) {}

  template<class... TS>
  bool match(reader<TS...> r) const
  {
    return r.get() == c_;
  }

private:
  char c_;
};

template<>
class grammar<std::string>
{
public:
  grammar(std::string s) : s_(s) {}

  template<class... TS>
  bool match(reader<TS...> r) const
  {
    for (auto c : s_)
      if (c != r.get())
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
  grammar(const char* s) : s_(s) {}

  template<class... TS>
  bool match(reader<TS...> r) const
  {
    return s_.match(r);
  }

private:
  grammar<std::string> s_;
};


ALEX_NAMESPACE_END

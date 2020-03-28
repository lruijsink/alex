#pragma once

#include <string>
#include "defines.h"
#include "grammar.h"
#include "reader.h"

namespace ALEX_NAMESPACE_NAME {


template<>
class grammar<char>
{
public:
  grammar(char c) : c_(c) {}

  bool read_and_test(detail::reader& r) const
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

  bool read_and_test(detail::reader& r) const
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

  bool read_and_test(detail::reader& r) const
  {
    return s_.read_and_test(r);
  }

private:
  grammar<std::string> s_;
};


}

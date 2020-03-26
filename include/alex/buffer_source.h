#pragma once

#include <string_view>
#include <string> // std::char_traits
#include "defines.h"

namespace ALEX_NAMESPACE_NAME {


template<class ViewT>
class buffer_source
{
public:
  using value_type = typename ViewT::value_type;
  using iterator   = typename ViewT::iterator;

  buffer_source(ViewT view)
    : view_(view)
  {
  }

  auto begin() const
  {
    return view_.begin();
  }

  auto end() const
  {
    return view_.end();
  }

private:
  ViewT view_;
};

template<>
class buffer_source<const char*> : public buffer_source<std::string_view>
{
public:
  buffer_source(const char* s)
    : buffer_source<std::string_view>(std::string_view(s))
  {
  }
};

template<class CharT, size_t SizeN>
class buffer_source<CharT[SizeN]>
{
public:
  using value_type = CharT;
  using iterator   = const value_type*;

  buffer_source(iterator begin)
    : begin_(begin)
    , end_(begin + SizeN - 1)
  {
  }

  auto begin()
  {
    return begin_;
  }

  auto end()
  {
    return end_;
  }

private:
  iterator begin_;
  iterator end_;
};


}

#pragma once

#define ALEX_NAMESPACE_BEGIN namespace alex {
#define ALEX_NAMESPACE_END }

#include "tag.h"

ALEX_NAMESPACE_BEGIN


template<class T, class... TS>
class grammar
{
public:
  grammar(T, TS...) = delete;
};

template<>
class grammar<tag::poly>;

template<class T, class... TS>
class reader
{
  reader(T, TS...) = delete;
};

template<>
class reader<tag::poly>;


ALEX_NAMESPACE_END

#pragma once

#define ALEX_NAMESPACE_BEGIN namespace alex {
#define ALEX_NAMESPACE_END }

ALEX_NAMESPACE_BEGIN


template<class T, class... TS>
class grammar
{
public:
  grammar(T, TS...) = delete;
};

template<class T, class... TS>
class reader
{
  reader(T, TS...) = delete;
};


ALEX_NAMESPACE_END

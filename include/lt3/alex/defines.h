#pragma once

#define LT3_ALEX_NAMESPACE_BEGIN namespace lt3 { namespace alex {
#define LT3_ALEX_NAMESPACE_END } }

LT3_ALEX_NAMESPACE_BEGIN


template<class T, class... TS>
class grammar
{
public:
  grammar(T, TS...) = delete;
};


LT3_ALEX_NAMESPACE_END

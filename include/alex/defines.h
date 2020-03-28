#pragma once

#define ALEX_NAMESPACE_NAME alex

#include "tag.h"

namespace ALEX_NAMESPACE_NAME {


template<class T, class... TS>
class grammar
{
public:
  grammar(T, TS...) = delete;
};


}

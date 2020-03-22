#pragma once

#include <type_traits>
#include "defines.h"
#include "stream_range.h"
#include "stream_forker.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class T, class = void, class = void>
struct is_streamable
  : std::false_type { };

template<class T>
struct is_streamable
  <
    T,
    std::void_t<decltype(&T::next)>,
    std::void_t<decltype(&T::eof)>
  >
  : std::true_type { };

template<class T, class = void, class = void, class = void>
struct is_range
  : std::false_type { };

template<class T>
struct is_range
  <
    T,
    std::void_t<typename T::value_type>,
    std::void_t<decltype(&T::begin)>,
    std::void_t<decltype(&T::end)>
  >
  : std::true_type { };

template<class T>
using make_streamable = std::conditional_t
  <
    is_streamable<T>::value,
    T,
    std::conditional_t
    <
      is_range<T>::value,
      stream_range<T>,
      void
    >
  >;

template<class T, class = void, class = void, class = void>
struct is_forkable_stream
  : std::false_type { };

template<class T>
struct is_forkable_stream
  <
    T,
    std::void_t<decltype(&T::fork)>,
    std::void_t<decltype(&T::join)>,
    std::void_t<decltype(&T::reset)>
  >
  : std::true_type { };

template<class T>
using make_fork_streamable = std::conditional_t
  <
    is_forkable_stream<make_streamable<T>>::value,
    make_streamable<T>,
    stream_forker<make_streamable<T>>
  >;


LT3_ALEX_NAMESPACE_END

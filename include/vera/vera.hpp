#pragma once
#include <type_traits>
namespace vera {

template <class... TS>
struct Pack {
  static constexpr size_t size = sizeof...(TS);
};

namespace detail {
template <class... TS>
struct UnpackHelper;
template <class... TS, class... P, class... R>
struct UnpackHelper<Pack<TS...>, Pack<P...>, R...>
    : public UnpackHelper<Pack<TS..., P...>, R...> {};
template <class... TS, class T, class... R>
struct UnpackHelper<Pack<TS...>, T, R...>
    : public UnpackHelper<Pack<TS..., T>, R...> {};
template <class... TS>
struct UnpackHelper<Pack<TS...> > {
  using type = Pack<TS...>;
};

template <template <class...> class TT, class T>
struct ApplyHelper;
template <template <class...> class TT, class... TS>
struct ApplyHelper<TT, Pack<TS...> > {
  using type = TT<TS...>;
};

template <template <class> class TT, class T>
struct TransformHelper;
template <template <class> class TT, class... TS>
struct TransformHelper<TT, Pack<TS...> > {
  using type = Pack<TT<TS>...>;
};

template <class Args, class Res = Pack<> >
struct ReverseHelper;
template <class T, class... TS, class... Res>
struct ReverseHelper<Pack<T, TS...>, Pack<Res...> >
    : public ReverseHelper<Pack<TS...>, Pack<T, Res...> > {};
template <class... Res>
struct ReverseHelper<Pack<>, Pack<Res...> > {
  using type = Pack<Res...>;
};

template <int Pos, class Args>
struct AtHelper;
template <class T, class... TS>
struct AtHelper<0, Pack<T, TS...> > {
  using type = T;
};
template <int Pos, class T, class... TS>
struct AtHelper<Pos, Pack<T, TS...> > : public AtHelper<Pos - 1, Pack<TS...> > {
};

template <int Count, class Args, class Res = Pack<> >
struct FirstNHelper;
template <class Arg, class... Rest, class... Res>
struct FirstNHelper<0, Pack<Arg, Rest...>, Pack<Res...> > {
  using type = Pack<Res...>;
};
template <int Count, class... Res>
struct FirstNHelper<Count, Pack<>, Pack<Res...> > {
  using type = Pack<Res...>;
};
template <int Count, class Arg, class... Rest, class... Res>
struct FirstNHelper<Count, Pack<Arg, Rest...>, Pack<Res...> >
    : public FirstNHelper<Count - 1, Pack<Rest...>, Pack<Res..., Arg> > {};

template <class T, class O = void>
struct CallableHelper : public CallableHelper<decltype(&T::operator())> {};
template <class O, class T, class... TS>
struct CallableHelper<T(TS...), O> {
  using objectType = O;
  using returnType = T;
  using arguments = Pack<TS...>;
};
template <class T, class... TS>
struct CallableHelper<T (*)(TS...)> : public CallableHelper<T(TS...), void> {};
template <class O, class T, class... TS>
struct CallableHelper<T (O::*)(TS...)> : public CallableHelper<T(TS...), O> {};
template <class O, class T, class... TS>
struct CallableHelper<T (O::*)(TS...) const>
    : public CallableHelper<T(TS...), O> {};

template <template <class> class Predicate, class ArgPack,
          class Result = Pack<> >
struct FilterHelper;
template <template <class> class P, class T, class... TS, class... RS>
struct FilterHelper<P, Pack<T, TS...>, Pack<RS...> > {
  using next = std::conditional_t<P<T>::value, Pack<RS..., T>, Pack<RS...> >;
  using type = typename FilterHelper<P, Pack<TS...>, next>::type;
};
template <template <class> class P, class... RS>
struct FilterHelper<P, Pack<>, Pack<RS...> > {
  using type = Pack<RS...>;
};

template <template <class> class Predicate, class ArgPack>
struct AllMatchHelper;
template <template <class> class P, class T, class... TS>
struct AllMatchHelper<P, Pack<T, TS...> > {
  static constexpr bool value =
      P<T>::value && AllMatchHelper<P, Pack<TS...> >::value;
};
template <template <class> class P>
struct AllMatchHelper<P, Pack<> > : std::true_type {};

template <template <class> class Predicate, class ArgPack>
struct AnyMatchHelper;
template <template <class> class P, class T, class... TS>
struct AnyMatchHelper<P, Pack<T, TS...> > {
  static constexpr bool value =
      P<T>::value || AnyMatchHelper<P, Pack<TS...> >::value;
};
template <template <class> class P>
struct AnyMatchHelper<P, Pack<> > : std::false_type {};

template <class Key, class ArgPack>
struct ContainsHelper;
template <class Key, class T, class... TS>
struct ContainsHelper<Key, Pack<T, TS...> > {
  static constexpr bool value =
      std::is_same_v<Key, T> || ContainsHelper<Key, Pack<TS...> >::value;
};
template <class Key>
struct ContainsHelper<Key, Pack<> > {
  static constexpr bool value = false;
};

}  // namespace detail

template <class... TS>
using unpack = typename detail::UnpackHelper<Pack<>, TS...>::type;

template <template <class...> class TT, class... TS>
using apply = typename detail::ApplyHelper<TT, unpack<TS...> >::type;

template <template <class> class TT, class... TS>
using transform = typename detail::TransformHelper<TT, unpack<TS...> >::type;

template <class... TS>
using reverse = typename detail::ReverseHelper<unpack<TS...> >::type;

template <int Pos, class... TS>
using at = typename detail::AtHelper<Pos, unpack<TS...> >::type;

template <class... TS>
using front = at<0, TS...>;

template <class... TS>
using back = at<unpack<TS...>::size - 1, TS...>;

template <int Count, class... TS>
using firstN = typename detail::FirstNHelper<Count, unpack<TS...> >::type;

template <int Count, class... TS>
using lastN = reverse<firstN<Count, reverse<TS...> > >;

template <int Count, class... TS>
using dropFront = lastN<unpack<TS...>::size - Count, TS...>;

template <int Count, class... TS>
using dropBack = firstN<unpack<TS...>::size - Count, TS...>;

template <int Start, int Count, class... TS>
using subset = firstN<Count, dropFront<Start, TS...> >;

template <class T>
using funcArgs = typename detail::CallableHelper<T>::arguments;

template <class T>
using returnType = typename detail::CallableHelper<T>::returnType;

template <class T>
using funcObject = typename detail::CallableHelper<T>::objectType;

template <template <class> class Predicate, class... Args>
using filter = typename detail::FilterHelper<Predicate, unpack<Args...> >::type;

template <template <class> class Predicate, class... Args>
using allMatch = detail::AllMatchHelper<Predicate, unpack<Args...> >;

template <template <class> class Predicate, class... Args>
constexpr bool allMatch_v = allMatch<Predicate, Args...>::value;

template <template <class> class Predicate, class... Args>
using anyMatch = detail::AnyMatchHelper<Predicate, unpack<Args...> >;

template <template <class> class Predicate, class... Args>
constexpr bool anyMatch_v = anyMatch<Predicate, Args...>::value;

template <class Key, class... Args>
using contains = detail::ContainsHelper<Key, unpack<Args...> >;

template <class Key, class... Args>
bool constexpr contains_v = contains<Key, Args...>::value;
namespace detail {
struct Placeholder;

template <class Args, class BoundPacks, class Result = Pack<> >
struct BindResolver;
template <class T, class... TS, class... P, class... PS, class... R>
struct BindResolver<Pack<T, TS...>, Pack<Pack<P...>, PS...>, Pack<R...> >
    : BindResolver<Pack<TS...>, Pack<PS...>, Pack<R..., P..., T> > {};
template <class... P, class... PS, class... R>
struct BindResolver<Pack<>, Pack<Pack<P...>, PS...>, Pack<R...> >
    : BindResolver<Pack<>, Pack<PS...>, Pack<R..., P...> > {};
template <class... TS, class... R>
struct BindResolver<Pack<TS...>, Pack<>, Pack<R...> >
    : BindResolver<Pack<>, Pack<>, Pack<R..., TS...> > {};
template <class... R>
struct BindResolver<Pack<>, Pack<>, Pack<R...> > {
  using type = Pack<R...>;
};

template <class Args, class Intermediate = Pack<>, class Result = Pack<> >
struct BindPacker;
template <class T, class... TS, class... I, class... R>
struct BindPacker<Pack<T, TS...>, Pack<I...>, Pack<R...> >
    : BindPacker<Pack<TS...>, Pack<I..., T>, Pack<R...> > {};
template <class... TS, class... I, class... R>
struct BindPacker<Pack<Placeholder, TS...>, Pack<I...>, Pack<R...> >
    : BindPacker<Pack<TS...>, Pack<>, Pack<R..., Pack<I...> > > {};
template <class... I, class... R>
struct BindPacker<Pack<>, Pack<I...>, Pack<R...> >
    : public BindPacker<Pack<>, Pack<>, Pack<R..., Pack<I...> > > {};
template <class... R>
struct BindPacker<Pack<>, Pack<>, Pack<R...> > {
  using type = Pack<R...>;
};

template <template <class...> class TT, class Args = Pack<> >
struct BindHelper {
  template <class... TS>
  using type =
      apply<TT, typename BindResolver<unpack<TS...>,
                                      typename BindPacker<Args>::type>::type>;
};

}  // namespace detail

template <template <class...> class TT, class... TS>
using bind = detail::BindHelper<TT, unpack<TS...> >;

using ph = detail::Placeholder;

}  // namespace vera

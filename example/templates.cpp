
struct reader
{
  const char* source_;
  const char* it_;

  reader(const char* source)
    : source_(source)
    , it_(source)
  {
  }

  template<class T>
  bool match()
  {
    auto fork_point = it_;
    auto matches = T::test(*this);
    if (!matches)
      it_ = fork_point;
    return matches;
  }

  int get()
  {
    if (*it_ != 0)
      return *(it_++);
    else
      return -1;
  }

  bool eof()
  {
    return *it_ == 0;
  }
};

template<char C>
struct eq_c
{
  static bool test(reader& r)
  {
    return r.get() == C;
  }
};

template<char From, char To>
struct from_to
{
  static bool test(reader& r)
  {
    auto v = r.get();
    return From <= v && v <= To;
  }
};

template<class... TS>
struct one_of
{
  static bool test(reader& r)
  {
    return (... || r.match<TS>());
  }
};

template<class... TS>
struct seq
{
  static bool test(reader& r)
  {
    return (... && r.match<TS>());
  }
};

template<class G, class S = void>
struct repeat
{
  static bool test(reader& r)
  {
    if (r.match<G>())
      while (r.match<seq<S, G>>()) {}
    return true;
  }
};

template<class G>
struct repeat<G, void>
{
  static bool test(reader& r)
  {
    while (r.match<G>()) {}
    return true;
  }
};

template<int N, class G, class S = void>
struct repeat_min
{
  static bool test(reader& r)
  {
    int c = 0;
    if (r.match<G>())
      while (r.match<seq<S, G>>())
        c++;
    return c >= N;
  }
};

template<int N, class G>
struct repeat_min<N, G, void>
{
  static bool test(reader& r)
  {
    int c = 0;
    while (r.match<seq<G>>())
      c++;
    return c >= N;
  }
};

template<const char* S>
struct s_eq
{
  static bool test(reader& r)
  {
    for (auto it = S; *it != 0; it++)
      if (*it != r.get())
        return false;
    return true;
  }
};

template<class T>
struct optional
{
  static bool test(reader& r)
  {
    r.match<T>();
    return true;
  }
};

struct any
{
  static bool test(reader& r)
  {
    r.get();
    return !r.eof();
  }
};

template<class T>
struct neq
{
  static bool test(reader& r)
  {
    return !r.match<T>();
  }
};

struct expr;

using ws =
repeat<
  one_of<
    eq_c<' '>,
    eq_c<'\t'>,
    eq_c<'\r'>,
    eq_c<'\n'>
  >
>;

template<char C>
using op =
seq<
  ws,
  eq_c<C>,
  ws
>;

using string_v =
seq<
  eq_c<'"'>,
  one_of<
    seq<
      eq_c<'\\'>,
      any
    >,
    neq<eq_c<'"'>>
  >,
  eq_c<'"'>
>;

using int_v =
one_of<
  eq_c<'0'>,
  seq<
    optional<
      eq_c<'-'>
    >,
    from_to<'1', '9'>,
    repeat<
      from_to<'0', '9'>
    >
  >
>;

using digits_v =
repeat_min<1,
  from_to<'0', '9'>
>;

using float_v =
seq<
  int_v,
  optional<
    seq<
      eq_c<'.'>,
      digits_v
    >
  >
>;

using exponent_v =
seq<
  one_of<
    eq_c<'e'>,
    eq_c<'E'>
  >,
  optional<
    one_of<
      eq_c<'-'>,
      eq_c<'+'>
    >
  >,
  digits_v
>;

using number_v =
seq<
  float_v,
  optional<
    exponent_v
  >
>;

using object_field_v =
seq<
  string_v,
  op<':'>,
  expr
>;

using object_v =
seq<
  op<'{'>,
  repeat<
    object_field_v,
    op<','>
  >,
  op<'}'>
>;

using array_v =
seq<
  op<'['>,
  repeat<
    expr,
    op<','>
  >,
  op<']'>
>;

constexpr const char null_s[] = "null";
using null_v = s_eq<null_s>;

constexpr const char true_s[] = "true";
using true_v = s_eq<true_s>;

constexpr const char false_s[] = "false";
using false_v = s_eq<false_s>;

struct expr : public
seq<
  ws,
  one_of
  <
    array_v,
    object_v,
    string_v,
    number_v,
    null_v,
    true_v,
    false_v
  >,
  ws
> {};

int main()
{
  return reader("null").match<expr>() ? 1234 : 5678;
}

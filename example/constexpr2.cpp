
struct reader
{
  const char* source_;
  const char* it_;

  constexpr reader(const char* source)
    : source_(source)
    , it_(source)
  {
  }

  template<class T>
  constexpr bool match(T g)
  {
    auto fork_point = it_;
    auto matches = g(*this);
    if (!matches)
      it_ = fork_point;
    return matches;
  }

  constexpr int get()
  {
    if (*it_ != 0)
      return *(it_++);
    else
      return -1;
  }

  constexpr bool eof()
  {
    return *it_ == 0;
  }
};

#include <type_traits>
#include <string_view>

template<class T>
constexpr auto make_lex(T v)
-> std::enable_if_t<std::is_invocable_v<T, reader&>, T>
{
  return v;
}

constexpr auto make_lex(char c)
{
  return [c] (reader& r)
  {
    return r.get() == c;
  };
};

constexpr auto make_lex(std::string_view s)
{
  return [s] (reader& r)
  {
    for(auto c : s)
      if(r.get() != c)
        return false;

    return true;
  };
};

constexpr auto make_lex(const char* s)
{
  return make_lex(std::string_view(s));
}

constexpr auto from_to = [] (auto from, auto to)
{
  return [from, to] (reader& r)
  {
    auto v = r.get();
    return from <= v && v <= to;
  };
};

constexpr auto any = [] (reader& r)
{
  return r.get() != -1;
};

constexpr auto eof = [] (reader& r)
{
  return r.eof();
};

constexpr auto any_but = [] (auto g)
{
  return [g] (reader& r)
  {
    return !make_lex(g)(r);
  };
};

constexpr auto seq = [] (auto... gs)
{
  return [gs...] (reader& r)
  {
    return (r.match(make_lex(gs)) && ...);
  };
};

template<class L, class R>
constexpr auto operator+(L l, R r)
{
  return seq(l, r);
}

constexpr auto one_of = [] (auto... gs)
{
  return [gs...] (reader& r)
  {
    return (r.match(make_lex(gs)) || ...);
  };
};

template<class L, class R>
constexpr auto operator||(L l, R r)
{
  return one_of(l, r);
}

constexpr auto optional = [] (auto g)
{
  return [g] (reader& r)
  {
    r.match(make_lex(g));
    return true;
  };
};

template<class G>
constexpr auto repeat(G g)
{
  auto mg = make_lex(g);
  return [mg] (reader& r)
  {
    while(r.match(mg)) {}
    return true;
  };
}

template<class G>
constexpr auto repeat_min(int n, G g)
{
  auto mg = make_lex(g);
  return [n, mg] (reader& r)
  {
    int c = 0;
    while(r.match(mg))
      c++;
    return c >= n;
  };
}

template<class G, class S>
constexpr auto repeat(G g, S s)
{
  auto mg = make_lex(g);
  auto ms = seq(s, mg);
  return [mg, ms] (reader& r)
  {
    if(r.match(mg))
      while(r.match(ms)) {}
    return true;
  };
}

template<class G, class S>
constexpr auto repeat_min(int n, G g, S s)
{
  auto mg = make_lex(g);
  auto ms = seq(s, mg);
  return [n, mg, ms] (reader& r)
  {
    int c = 0;
    if(r.match(mg))
    {
      c++;
      while(r.match(ms))
        c++;
    }
    return c >= n;
  };
}

bool expression_v(reader& r);

constexpr auto ws = repeat(one_of(' ', '\t', '\r', '\n'));
constexpr auto op = [] (auto g) { return ws + g + ws; };

constexpr auto string_v = '"' + repeat(('\\' + any) || any_but('"')) + '"';

constexpr auto int_v = optional('-') + ('0' || (from_to('1', '9') + repeat(from_to('0', '9'))));
constexpr auto fraction_v = '.' + repeat_min(1, from_to('0', '9'));
constexpr auto exponent_v = one_of('e', 'E') + optional(one_of('-', '+')) + repeat_min(1, from_to('0', '9'));
constexpr auto number_v = int_v + optional(fraction_v) + optional(exponent_v);

constexpr auto keyword_v = one_of("null", "true", "false");

constexpr auto array_v = op('[') + repeat(expression_v, op(',')) + op(']');
constexpr auto object_v = op('{') + repeat(string_v + op(':') + expression_v, op(',')) + op('}');

constexpr auto json = ws + expression_v + ws;

bool expression_v(reader& r)
{
  return r.match(ws + (string_v || number_v || keyword_v || array_v || object_v) + ws);
}

int main()
{
  auto r = reader("null");
  auto m = r.match(json);
  auto o = m ? 1234 : 5678;
  return o;
}

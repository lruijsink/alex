#pragma once

#include <string>
#include <string_view>
#include "defines.h"
#include "grammar.h"
#include "symbol_tree.h"

namespace ALEX_NAMESPACE_NAME {


template<class StreamT>
class reader<StreamT>
{
public:
  using stream_type = StreamT;
  using traits_type = typename stream_type::traits_type;
  using char_type   = typename traits_type::char_type;
  using int_type    = typename traits_type::int_type;

  reader(stream_type& stream, symbol_tree* tree)
    : stream_(stream)
    , symbol_tree_it_(tree)
  {
  }

  auto get()
  {
    return stream_.get();
  }

  auto eof() const
  {
    return stream_.eof();
  }

  auto pos() const
  {
    return stream_.pos();
  }

  auto view(size_t begin, size_t end) const
  {
    return stream_.view(begin, end);
  }

  auto& begin_symbol(std::string name)
  {
    symbol_tree_it_ = &(symbol_tree_it_->emplace_back(name));
    return *symbol_tree_it_;
  }

  auto commit_symbol()
  {
    symbol_tree_it_ = &(symbol_tree_it_->parent());
  }

  auto discard_symbol()
  {
    symbol_tree_it_->parent().pop_back();
    symbol_tree_it_ = &(symbol_tree_it_->parent());
  }

  template<class... TS>
  auto parse(grammar<TS...> g)
  {
    auto fork_point = stream_.fork();
    auto matches = g.read_and_test(*this);

    if (matches)
      stream_.join(fork_point);
    else
      stream_.reset(fork_point);

    return matches;
  }

private:
  stream_type& stream_;
  symbol_tree* symbol_tree_it_;
};


}

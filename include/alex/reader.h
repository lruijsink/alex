#pragma once

#include <string>
#include <string_view>
#include "defines.h"
#include "grammar.h"
#include "symbol_tree.h"

namespace ALEX_NAMESPACE_NAME {


class reader
{
public:
  using source_type = std::string_view;
  using traits_type = typename source_type::traits_type;
  using char_type   = typename traits_type::char_type;
  using int_type    = typename traits_type::int_type;

  reader(source_type source, symbol_tree* tree)
    : source_(source)
    , read_it_(source.begin())
    , symbol_tree_it_(tree)
  {
  }

  auto get() -> int_type
  {
    return read_it_ != source_.end()
         ? *(read_it_++)
         : traits_type::eof();
  }

  auto eof() const
  {
    return read_it_ == source_.end();
  }

  auto pos() -> size_t const
  {
    return read_it_ - source_.begin();
  }

  auto view(size_t from, size_t to) const
  {
    return source_.substr(from, to - from);
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
    auto fork_point = read_it_;
    auto matches = g.read_and_test(*this);

    if (!matches)
      read_it_ = fork_point;

    return matches;
  }

private:
  source_type source_;
  source_type::iterator read_it_;
  symbol_tree* symbol_tree_it_;
};


}

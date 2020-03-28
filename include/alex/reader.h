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
  reader(std::string_view source)
    : source_(source)
    , read_it_(source.begin())
    , tree_()
    , symbol_tree_it_(&tree_)
  {
  }

  reader(const reader&) = delete;

  auto get() -> int
  {
    return read_it_ != source_.end()
         ? *(read_it_++)
         : std::char_traits<char>::eof();
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
  auto match(grammar<TS...> g)
  {
    auto fork_point = read_it_;
    auto matches = g.read_and_test(*this);

    if (!matches)
      read_it_ = fork_point;

    return matches;
  }

  auto tree()
  {
    return tree_;
  }

private:
  std::string_view source_;
  std::string_view::iterator read_it_;
  symbol_tree tree_;
  symbol_tree* symbol_tree_it_;
};


}

#pragma once

#include <string>
#include <vector>
#include "defines.h"

namespace ALEX_NAMESPACE_NAME
{


class symbol_tree
{
public:
  symbol_tree()
    : name_("root")
    , parent_(nullptr)
  {
  }

  symbol_tree(std::string name, symbol_tree* parent)
    : name_(name)
    , parent_(parent)
  {
  }

  auto name() const
  {
    return name_;
  }

  auto& parent() const
  {
    return *parent_;
  }

  const auto& leaves() const
  {
    return leaves_;
  }

  auto& emplace_back(std::string name)
  {
    return leaves_.emplace_back(name, this);
  }

  auto pop_back()
  {
    leaves_.pop_back();
  }

private:
  std::string name_;
  symbol_tree* parent_;
  std::vector<symbol_tree> leaves_;
};


}

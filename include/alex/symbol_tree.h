#pragma once

#include <string>
#include <string_view>
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

  symbol_tree(std::string name, symbol_tree* parent, const char* content_begin)
    : name_(name)
    , parent_(parent)
    , content_begin_(content_begin)
  {
  }

  auto name() const
  {
    return name_;
  }

  auto content() const
  {
    auto length = content_end_ - content_begin_;
    return std::string_view(content_begin_, length);
  }

  auto& parent() const
  {
    return *parent_;
  }

  const auto& leaves() const
  {
    return leaves_;
  }

  auto& emplace_back(std::string name, const char* content_begin)
  {
    return leaves_.emplace_back(name, this, content_begin);
  }

  auto pop_back()
  {
    leaves_.pop_back();
  }

  auto set_content_end(const char* content_end)
  {
    content_end_ = content_end;
  }

private:
  std::string name_;
  symbol_tree* parent_;
  const char* content_begin_;
  const char* content_end_;
  std::vector<symbol_tree> leaves_;
};


}

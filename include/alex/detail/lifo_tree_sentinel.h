#pragma once

namespace alex {
namespace detail {


struct lifo_tree_sentinel {
public:
  lifo_tree_sentinel(size_t index)
    : index_(index) {}

  auto index() const {
    return index_;
  }

private:
  const size_t index_;
};


}
}

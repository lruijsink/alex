#pragma once
#include <string_view>

namespace alex {

class lexing_context {
 public:
  constexpr lexing_context(std::string_view data) : data_(data) {}

  constexpr auto data() const noexcept { return data_; }
  constexpr auto advance(size_t count) const noexcept {
    return lexing_context(data_.substr(count));
  }

 private:
  std::string_view data_;
};

}  // namespace alex

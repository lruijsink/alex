#pragma once

namespace alex {


template<class TokenType, class ContentType>
class token_data {
public:
  using token_type = TokenType;
  using content_type = ContentType;

  token_data() {}

  token_data(const token_type& token)
    : token_(token) {}

  const auto& token() const {
    return token_;
  }

  auto& content() {
    return content_;
  }

  const auto& content() const {
    return content_;
  }

private:
  token_type token_;
  content_type content_;
};


}

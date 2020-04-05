#pragma once

#include "./token_tree_builder.h"

namespace alex {


template<class TokenType>
using token_tree = typename token_tree_builder<TokenType>::tree_type;


}

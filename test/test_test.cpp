#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

TEST_CASE("Test") {
  REQUIRE(true);
}

TEST_CASE("Test failure") {
  REQUIRE(false);
}

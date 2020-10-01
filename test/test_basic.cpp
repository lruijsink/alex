#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Test", "[basic]") { REQUIRE(true); }

TEST_CASE("Test failure", "[basic]") { REQUIRE(false); }

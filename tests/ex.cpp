#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Array.hpp"

TEST_CASE("Example test") {

    auto ar = CDCG::Array{1,2,3,4,5};
    REQUIRE(ar.size() == 5);



}
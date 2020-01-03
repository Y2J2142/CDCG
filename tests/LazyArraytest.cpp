#define CATCH_CONFIG_RUNNER  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_COLOUR_WINDOWS
#include <catch2/catch.hpp>

#include "LazyArray.hpp"

TEST_CASE("Default size and capacity") {

    CDCG::LazyArray<int, 10> ar {};


    REQUIRE( ar.size() == 0);
    REQUIRE( ar.capacity() == 10);
    REQUIRE( ar.empty() );

}

TEST_CASE( "Appending values") {
    CDCG::LazyArray<int, 10> ar {};

    ar.push_back(1);
    ar.push_back(1);
    ar.push_back(1);

    REQUIRE( ar.size() == 3);
    REQUIRE( !ar.empty() );

}

TEST_CASE( "Getting values from the array") {
    CDCG::LazyArray<int, 10> ar {};

    ar.push_back(1);
    ar.push_back(1);
    ar.push_back(1);
    REQUIRE( ar.size() == 3);
    REQUIRE( ar[0] == 1 );
    REQUIRE( ar[1] == 1 );
    REQUIRE( ar.at(2) == 1 );
}

TEST_CASE( "Clearing the array") {
    CDCG::LazyArray<int, 10> ar {};
    
    ar.push_back(1);
    ar.push_back(1);
    ar.push_back(1);


    ar.clear();
    REQUIRE( ar.size() == 0);
    REQUIRE( ar.empty() );


}


int main(int argc, char* argv[])
{

    int result = Catch::Session().run(argc, argv);

    return result;
}
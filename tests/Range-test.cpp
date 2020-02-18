#define CATCH_CONFIG_RUNNER  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>


#include "Range.hpp"
#include <vector>

using CDCG::Range;

TEST_CASE("Range size calculation for integral ranges") {



    SECTION("Only end of range specified") {
        Range r{10};
        REQUIRE( r.size() == 10 );
    }
    SECTION("End and begin of range specified") {
        Range r2{2, 10};
        REQUIRE( r2.size() == 8 );
    }
    SECTION("End, begin and step of range specified") {
        Range r3{1, 10, 2};
        REQUIRE( r3.size() == 4 );
    }




}

TEST_CASE("Range size calculation for floating point ranges") {



    SECTION("Only end of range specified") {
        Range r{10.f};
        REQUIRE( r.size() == 10 );
    }
    SECTION("End and begin of range specified") {
        Range r2{2.f, 10.f};
        REQUIRE( r2.size() == 8 );
    }
    SECTION("End, begin and step of range specified") {
        Range r3{0.f, 10.f, 0.1f};
        REQUIRE( r3.size() == 100 );
    }

}


TEST_CASE("Iteration over integral range") {



    SECTION("Only end of range specified") {
        std::vector<int> vec{}; 
        for(auto i : Range{10})
            vec.push_back(i); 

        REQUIRE( std::vector{0,1,2,3,4,5,6,7,8,9} == vec );
    }

    SECTION("End and begin of range specified") {
        std::vector<int> vec{}; 
        for(auto i : Range{1, 10})
            vec.push_back(i); 

        REQUIRE( std::vector{1,2,3,4,5,6,7,8,9} == vec );
    }

    SECTION("End, begin and step of range specified") {
        std::vector<int> vec{}; 
        for(auto i : Range{1, 10, 2})
            vec.push_back(i); 

        REQUIRE( std::vector{1,3,5,7,9} == vec );
    }


}

//Testing for equality with floating point aint the best idea but its honest work
TEST_CASE("Iteration over floating point range") {



    SECTION("Only end of range specified") {
        std::vector<float> vec{}; 
        for(auto i : Range{10.f})
            vec.push_back(i); 

        REQUIRE( std::vector{0.f,1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f} == vec );
    }

    SECTION("End and begin of range specified") {
        std::vector<float> vec{}; 
        for(auto i : Range{1.f, 10.f})
            vec.push_back(i); 

        REQUIRE( std::vector{1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f} == vec );
    }

    SECTION("End, begin and step of range specified") {
        std::vector<float> vec{}; 
        for(auto i : Range{0.f, 10.f, 2.f})
            vec.push_back(i); 

        REQUIRE( std::vector{0.f,2.f,4.f,6.f,8.f} == vec );
    }


}




int main(int argc, char* argv[])
{

    int result = Catch::Session().run(argc, argv);

    return result;
}

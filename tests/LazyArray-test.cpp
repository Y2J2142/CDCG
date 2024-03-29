#include <catch2/catch_test_macros.hpp>

#include "LazyArray.hpp"

TEST_CASE("Default size and capacity")
{

	CDCG::LazyArray<int, 10> ar{};

	REQUIRE(ar.size() == 0);
	REQUIRE(ar.capacity() == 10);
	REQUIRE(ar.empty());
}

TEST_CASE("Appending values")
{
	CDCG::LazyArray<int, 10> ar{};

	ar.push_back(1);
	ar.push_back(1);
	ar.push_back(1);

	REQUIRE(ar.size() == 3);
	REQUIRE(!ar.empty());
}

TEST_CASE("Getting values from the array")
{
	CDCG::LazyArray<int, 10> ar{};

	ar.push_back(1);
	ar.push_back(1);
	ar.push_back(1);
	REQUIRE(ar.size() == 3);
	REQUIRE(ar[0] == 1);
	REQUIRE(ar[1] == 1);
	REQUIRE(ar.at(2) == 1);
}

TEST_CASE("Clearing the array")
{
	CDCG::LazyArray<int, 10> ar{};

	ar.push_back(1);
	ar.push_back(1);
	ar.push_back(1);

	ar.clear();
	REQUIRE(ar.size() == 0);
	REQUIRE(ar.empty());
}

TEST_CASE("Equality Compare")
{
	CDCG::LazyArray<int, 15> ar1 = { 1, 2, 3, 4, 5 };
	CDCG::LazyArray<int, 5> ar2{};
	ar2.emplace_back(1);
	ar2.emplace_back(2);
	ar2.emplace_back(3);
	ar2.emplace_back(4);
	ar2.emplace_back(5);

	REQUIRE(ar1 == ar2);
	ar1.emplace_back(3);
	REQUIRE(ar1 != ar2);
}

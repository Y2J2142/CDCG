#include "SmallVector.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>
using namespace CDCG;

TEST_CASE("SmallVector construction")
{
	SECTION("Default construction")
	{
		SmallVector<int, 10> sv{};
		REQUIRE(sv.size() == 0);
		REQUIRE(sv.empty() == true);
		REQUIRE(sv.capacity() == 10);
	}
}
TEST_CASE("SmallVector Initializer list construction")
{

	SECTION("Initializer list construction")
	{
		SmallVector<int, 5> sv{ 1, 2, 3, 4, 5 };
		REQUIRE(sv[0] == 1);
		REQUIRE(sv[1] == 2);
		REQUIRE(sv[2] == 3);
		REQUIRE(sv[3] == 4);
		REQUIRE(sv[4] == 5);
		REQUIRE(sv.size() == 5);
		REQUIRE(sv.isSmall() == true);
	}
	SECTION(
		"Initializer list construction with element count higher than capacity")
	{
		SmallVector<int, 1> sv{ 1, 2, 3, 4, 5 };
		REQUIRE(sv.isSmall() == false);
		REQUIRE(sv.size() == 5);
	}
}
TEST_CASE("SmallVector copying")
{
	SECTION("Copy construction")
	{
		const SmallVector<int, 3> sv{ 1, 2, 3 };
		SmallVector<int, 3> sv2{ sv };
		REQUIRE(sv.size() == sv2.size());
		REQUIRE(sv[0] == sv2[0]);
		REQUIRE(sv[1] == sv2[1]);
		REQUIRE(sv[2] == sv2[2]);
	}
	SECTION("Copy construction from SmallVector with bigger buffer size")
	{
		const SmallVector<std::string, 5> sv{ "a", "b", "c", "d", "e" };
		SmallVector<std::string, 2> sv2{ sv };
		REQUIRE(sv.size() == sv2.size());
		for (int i = 0; i < sv.size(); i++)
			REQUIRE(sv[i] == sv2[i]);
	}
	SECTION("Copy construction from SmallVector with smaller buffer size")
	{
		const SmallVector<float, 4> sv{ 1.f, 2.f, 3.f, 4.f };
		SmallVector<float, 5> sv2{ sv };
		REQUIRE(sv2.isSmall());
		REQUIRE(sv2.capacity() == 5);
		REQUIRE(sv2.size() == sv.size());
		for (int i = 0; i < sv.size(); i++)
			REQUIRE(sv[i] == sv2[i]);
	}
}
TEST_CASE("SmallVector insertion")
{

	SECTION("Insertion")
	{
		SmallVector<std::string, 10> sv{};
		std::string s1{ "string1" };
		sv.push_back(s1);
		sv.emplace_back(std::string{ "string2" });
		sv.push_back(std::string(s1.rbegin(), s1.rend()));
		REQUIRE(sv.size() == 3);
		REQUIRE(sv.capacity() == 10);
		REQUIRE(sv[0] == "string1");
		REQUIRE(sv[1] == "string2");
		REQUIRE(sv[2] == "1gnirts");
	}
	SECTION("Growing past small buffer")
	{
		SmallVector<int, 2> sv{};
		sv.push_back(1);
		sv.push_back(2);
		sv.push_back(3);
		REQUIRE(sv.isSmall() == false);
	}
}

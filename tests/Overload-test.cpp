#define CATCH_CONFIG_RUNNER // This tells Catch to provide a main() - only do
							// this in one cpp file
#include <catch2/catch.hpp>

#include "Overload.hpp"
#include <array>
#include <type_traits>
#include <variant>

TEST_CASE("Overload usage")
{

	using Variant = std::variant<int, double, char>;

	auto overload = CDCG::Overload{ [](int) { return 1; },
									[](double) { return 2; },
									[](char) { return 3; } };

	std::array<Variant, 3> ar = { 1, 2.0, '3' };

	REQUIRE(std::visit(overload, ar[0]) == 1);
	REQUIRE(std::visit(overload, ar[1]) == 2);
	REQUIRE(std::visit(overload, ar[2]) == 3);
}

int
main(int argc, char* argv[])
{

	int result = Catch::Session().run(argc, argv);

	return result;
}

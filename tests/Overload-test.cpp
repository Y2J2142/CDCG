#include "Overload.hpp"
#include <array>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
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

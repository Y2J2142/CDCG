#include <catch2/catch_test_macros.hpp>

#include "compose.hpp"

TEST_CASE("Compose usage")
{

	auto f = [](int i) { return i * 2; };
	auto g = [](int i) { return i + 3; };
	auto h = [](int i) { return i * 4; };
	auto j = [](int i) { return i + 5; };

	auto compose = CDCG::compose(f, g, h, j);
	REQUIRE(compose(10) == f(g(h(j(10)))));
}

TEST_CASE("ComposeRight usage")
{

	auto f = [](int i) { return i * 2; };
	auto g = [](int i) { return i + 3; };
	auto h = [](int i) { return i * 4; };
	auto j = [](int i) { return i + 5; };

	auto composeRight = CDCG::composeRight(f, g, h, j);
	REQUIRE(composeRight(10) == j(h(g(f(10)))));
}

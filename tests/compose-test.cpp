#define CATCH_CONFIG_RUNNER // This tells Catch to provide a main() - only do
							// this in one cpp file
#include <catch2/catch.hpp>

#include "compose.hpp"

TEST_CASE("Compose usage")
{

	auto f = [](int i) { return i * 2; };
	auto g = [](int i) { return i + 3; };
	auto h = [](int i) { return i * 4; };
	auto i = [](int i) { return i + 5; };

	auto compose = CDCG::compose(f, g, h, i);
	REQUIRE(compose(10) == f(g(h(i(10)))));
}

TEST_CASE("ComposeRight usage")
{

	auto f = [](int i) { return i * 2; };
	auto g = [](int i) { return i + 3; };
	auto h = [](int i) { return i * 4; };
	auto i = [](int i) { return i + 5; };

	auto composeRight = CDCG::composeRight(f, g, h, i);
	REQUIRE(composeRight(10) == i(h(g(f(10)))));
}

int
main(int argc, char* argv[])
{

	int result = Catch::Session().run(argc, argv);

	return result;
}

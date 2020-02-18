#include "Overload.hpp"
#include <iostream>
#include <variant>
#include <vector>

int
main()
{

	using var = std::variant<int, double, char>;

	auto vec = std::vector<var>{ 1, 2.0, '3' };

	auto ovrld = CDCG::Overload{ [](int) { std::cout << "int\n"; },
								 [](double) { std::cout << "double\n"; },
								 [](char) { std::cout << "char\n"; }

	};

	for (auto&& v : vec) {

		std::visit(ovrld, v);
	}

	return 0;
}
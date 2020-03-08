#include "compose.hpp"
#include <iostream>
int
main()
{
	auto f = [](int i) {
		std::cout << "F";
		return i * 2;
	};
	auto g = [](int i) {
		std::cout << "g";
		return i + 3;
	};
	auto h = [](int i) {
		std::cout << "h";

		return i * 4;
	};
	auto j = [](int i) {
		std::cout << "i";

		return i + 5;
	};

	auto composeRight = CDCG::composeRight(f, g, h, j);
	auto compose = CDCG::compose(f, g, h, j);

	std::cout << "compose = " << compose(10) << std::endl;
	std::cout << "composeRight = " << composeRight(10) << std::endl;

	return 0;
}

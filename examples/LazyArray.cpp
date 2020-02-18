#include "LazyArray.hpp"
#include <iostream>
#include <vector>

using namespace CDCG;

int
main()
{

	LazyArray<int, 10> ar;
	for (int i = 0; i < 10; ++i)
		ar.push_back(i);
	for (auto i : ar)
		std::cout << i << ' ';

	std::cout << '\n';

	LazyArray<int, 6> ar2{ 1, 2, 3, 4, 5 };
	for (auto i : ar2)
		std::cout << i << ' ';

	std::cout << '\n';

	LazyArray<std::vector<int>, 10> ar3{ { 1, 2, 3, 4 },
										 { 1, 2, 3, 4 },
										 { 1, 2, 3, 4 } };
}
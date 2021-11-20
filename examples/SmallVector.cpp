#include "SmallVector.hpp"
#include <assert.h>
#include <iostream>
#include <vector>

struct alignas(128) Overaligned
{};

using namespace CDCG;

int
main()
{

	SmallVector<Overaligned, 3> d;
	std::cout << std::boolalpha << "Overaligned : " << d.isSmall() << std::endl;
	d.emplace_back();
	d.emplace_back();
	d.emplace_back();
	d.emplace_back();
	d.emplace_back();
	d.emplace_back();
	d.emplace_back();

	SmallVector<std::vector<int>, 5> test2;
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });
	test2.emplace_back(std::vector<int>{ 1, 2, 3, 4, 5 });

	SmallVector<std::vector<int>, 10> test3{ std::move(test2) };

	std::cout << std::boolalpha << test3.isSmall() << std::endl;
	for (auto&& i : test3)
		std::cout << i.size() << ' ';

	SmallVector<int, 5> test;
	test.push_back(1);
	test.push_back(1);
	test.push_back(1);
	test.push_back(1);

	SmallVector<int, 2> test4{ std::move(test) };

	std::cout << std::boolalpha << test4.isSmall() << std::endl;
	for (auto&& i : test4)
		std::cout << i << ' ';

	std::cout << '\n';
}
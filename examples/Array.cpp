#include "Array.hpp"

using namespace CDCG;

int
main()
{

	constexpr Array<int, 5> ar{ 1, 2, 3, 4, 5 };

	constexpr auto t = ar[2];
	(void)t;

	return ar[4];
}

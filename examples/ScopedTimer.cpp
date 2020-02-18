#include "ScopedTimer.hpp"
#include <chrono>
#include <thread>

using namespace CDCG;

int
main()
{
	ScopedTimer_ns t{ "test" };
	std::this_thread::sleep_for(std::chrono::seconds(1));

	"lieterals supported"_st_ns;
}
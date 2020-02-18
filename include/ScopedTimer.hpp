#pragma once

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <chrono>
#include <ratio>
#include <string>

namespace CDCG {

struct ScopedTimerBase
{
	std::chrono::system_clock::time_point start;
	const std::string msg;

  protected:
	ScopedTimerBase(std::string&&);
};

template<typename Resolution>
struct EXPORT ScopedTimer : public ScopedTimerBase
{

	ScopedTimer(std::string = "");
	~ScopedTimer();
};

using ScopedTimer_ns = ScopedTimer<std::chrono::nanoseconds>;
using ScopedTimer_ms = ScopedTimer<std::chrono::milliseconds>;
using ScopedTimer_us = ScopedTimer<std::chrono::microseconds>;
using ScopedTimer_s = ScopedTimer<std::chrono::seconds>;
using ScopedTimer_m = ScopedTimer<std::chrono::minutes>;
using ScopedTimer_h = ScopedTimer<std::chrono::hours>;

ScopedTimer_ns operator""_st_ns(const char* c, std::size_t)
{
	return ScopedTimer<std::chrono::nanoseconds>{ c };
}
ScopedTimer_ms operator""_st_ms(const char* c, std::size_t)
{
	return ScopedTimer<std::chrono::milliseconds>{ c };
}
ScopedTimer_us operator""_st_us(const char* c, std::size_t)
{
	return ScopedTimer<std::chrono::microseconds>{ c };
}
ScopedTimer_s operator""_st_s(const char* c, std::size_t)
{
	return ScopedTimer<std::chrono::seconds>{ c };
}
ScopedTimer_m operator""_st_m(const char* c, std::size_t)
{
	return ScopedTimer<std::chrono::minutes>{ c };
}
ScopedTimer_h operator""_st_h(const char* c, std::size_t)
{
	return ScopedTimer<std::chrono::hours>{ c };
}
}

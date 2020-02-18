#include "Debug.hpp"
#include <cstdio>
#include <iomanip>
#include <iostream>
namespace CDCG {

Debug::Debug(Debug::DebugLevel lvl)
	: file{ nullptr }
{
	switch (lvl) {
		case DebugLevel::STANDARD:
			file = stdout;
			break;
		case DebugLevel::ERROR:
			file = stderr;
			break;
	}
}

Debug::Debug()
	: file{ stdout }
{}

Debug&
Debug::operator<<(Debug::Color c)
{
	switch (c) {
		case Debug::Color::BLACK:
			fprintf(file, "\u001b[30m");
			break;
		case Debug::Color::RED:
			fprintf(file, "\u001b[31m");
			break;
		case Debug::Color::GREEN:
			fprintf(file, "\u001b[32m");
			break;
		case Debug::Color::YELLOW:
			fprintf(file, "\u001b[33m");
			break;
		case Debug::Color::BLUE:
			fprintf(file, "\u001b[34m");
			break;
		case Debug::Color::MAGENTA:
			fprintf(file, "\u001b[35m");
			break;
		case Debug::Color::CYAN:
			fprintf(file, "\u001b[36m");
			break;
		case Debug::Color::WHITE:
			fprintf(file, "\u001b[37m");
			break;
		case Debug::Color::RESET:
			fprintf(file, "\u001b[0m");
			break;
	}

	return *this;
}
Debug&
Debug::operator<<(Debug::BackgroundColor c)
{
	switch (c) {
		case Debug::BackgroundColor::BLACK:
			fprintf(file, "\u001b[40m");
			break;
		case Debug::BackgroundColor::RED:
			fprintf(file, "\u001b[41m");
			break;
		case Debug::BackgroundColor::GREEN:
			fprintf(file, "\u001b[42m");
			break;
		case Debug::BackgroundColor::YELLOW:
			fprintf(file, "\u001b[43m");
			break;
		case Debug::BackgroundColor::BLUE:
			fprintf(file, "\u001b[44m");
			break;
		case Debug::BackgroundColor::MAGENTA:
			fprintf(file, "\u001b[45m");
			break;
		case Debug::BackgroundColor::CYAN:
			fprintf(file, "\u001b[46m");
			break;
		case Debug::BackgroundColor::WHITE:
			fprintf(file, "\u001b[47m");
			break;
		case Debug::BackgroundColor::RESET:
			fprintf(file, "\u001b[0m");
			break;
	}

	return *this;
}

Debug&
Debug::operator<<(std::string_view sv)
{
	fprintf(file, "%.*s", static_cast<int>(sv.size()), sv.data());
	return *this;
}

Debug& Debug::operator<<(std::nullptr_t)
{
	fprintf(file, " null pointer");
	return *this;
}

Debug&
Debug::operator<<(const char* ccs)
{
	fprintf(file, "%s", ccs);
	return *this;
}

Debug&
Debug::operator<<(bool b)
{
	fprintf(file, b ? " true" : "false");
	return *this;
}
Debug&
Debug::operator<<(int val)
{
	fprintf(file, " %i ", val);
	return *this;
}
Debug&
Debug::operator<<(long val)
{
	fprintf(file, " %li ", val);
	return *this;
}
Debug&
Debug::operator<<(long long val)
{
	fprintf(file, " %lli ", val);
	return *this;
}
Debug&
Debug::operator<<(unsigned val)
{
	fprintf(file, " %ui ", val);
	return *this;
}
Debug&
Debug::operator<<(unsigned long val)
{
	fprintf(file, " %lu ", val);
	return *this;
}
Debug&
Debug::operator<<(unsigned long long val)
{
	fprintf(file, " %llu ", val);
	return *this;
}
Debug&
Debug::operator<<(float val)
{
	fprintf(file, " %.5f ", val);
	return *this;
}
Debug&
Debug::operator<<(double val)
{
	fprintf(file, " %.10lf ", val);
	return *this;
}
Debug&
Debug::operator<<(long double val)
{
	fprintf(file, " %.15Lf ", val);
	return *this;
}
Debug&
Debug::operator<<(void* val)
{
	fprintf(file, "%s", static_cast<char*>(val));
	return *this;
}

Debug&
Debug::operator<<(std::chrono::nanoseconds duration)
{
	fprintf(file, " %llins ", std::chrono::nanoseconds(duration).count());
	return *this;
}
Debug&
Debug::operator<<(std::chrono::microseconds duration)
{
	fprintf(file, " %llius ", std::chrono::microseconds(duration).count());
	return *this;
}
Debug&
Debug::operator<<(std::chrono::milliseconds duration)
{
	fprintf(file, " %llims ", std::chrono::milliseconds(duration).count());
	return *this;
}
Debug&
Debug::operator<<(std::chrono::seconds duration)
{
	fprintf(file, " %llis ", std::chrono::seconds(duration).count());
	return *this;
}
Debug&
Debug::operator<<(std::chrono::minutes duration)
{
	fprintf(file, " %llim ", std::chrono::minutes(duration).count());
	return *this;
}
Debug&
Debug::operator<<(std::chrono::hours duration)
{
	fprintf(file, " %llih ", std::chrono::hours(duration).count());
	return *this;
}

Debug::~Debug()
{
	fprintf(file, "\u001b[0m \n");
}

}

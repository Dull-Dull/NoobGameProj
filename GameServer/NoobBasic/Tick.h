#pragma once

#include <chrono>

namespace Noob
{

enum class TickUnit : long long
{
	Second = 1000000000LL,
	Minute = 60LL * Second,
	Hour = 60LL * Minute,
	Day = 24LL * Hour,
	Week = 7LL * Day
};

using Tick = std::chrono::system_clock::time_point;
//using Tick = std::chrono::duration<std::chrono::nanoseconds>;		// nano second

inline static Tick GetTick()
{
	return std::chrono::system_clock::now();
}

}
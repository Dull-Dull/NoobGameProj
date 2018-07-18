#pragma once

#include <chrono>

namespace Noob
{

using TickRatio = ::std::nano;
using Tick = long long;
using Duration = ::std::chrono::duration< Tick, TickRatio >;
using TimePoint = ::std::chrono::time_point<::std::chrono::system_clock, Duration>;

class ___CheckRatio
{
	static_assert( TickRatio::num == 1 &&
		TickRatio::den > 1 &&
		TickRatio::den % 10 == 0,
		"TickRatio Is Wrong" );

	static_assert( ::std::is_integral<Tick>::value,
		"Tick Should Be Integer Type" );
};

enum E_TICK_UNIT : Tick
{
	Second = TickRatio::den,
	Minute = 60 * Second,
	Hour = 60 * Minute,
	Day = 24 * Hour,
	Week = 7 * Day
};

inline Tick GetTick()
{
	return ::std::chrono::duration_cast<Duration>
		( ::std::chrono::system_clock::now().time_since_epoch() ).count();
}

inline TimePoint GetNow()
{
	return ::std::chrono::time_point_cast<Duration>( ::std::chrono::system_clock::now() );
}

}
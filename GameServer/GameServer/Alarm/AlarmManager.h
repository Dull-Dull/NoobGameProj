#pragma once

#include "AlarmTask.h"

class GameDispatcher;

class AlarmManager
{
public:
	AlarmManager( GameDispatcher* dispatcher );
	~AlarmManager();
	
	int64_t RegisterAlarm( const ::Noob::Duration& duration,  AlarmCallback callback );
	int64_t RegisterAlarm( const ::Noob::TimePoint& timePoint,  AlarmCallback callback );
	void UnRegisterAlarm( int64_t alarmIndex );

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};
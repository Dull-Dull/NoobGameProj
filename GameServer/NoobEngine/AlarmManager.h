#pragma once

#include "AlarmTask.h"

namespace Noob
{

class Dispatcher;

#pragma todo �����İ� �̱۽������� ��쿡�� ���� �۵�����, �����ؾ���.
class AlarmManager
{
public:
	AlarmManager( Dispatcher* dispatcher );
	~AlarmManager();

	int64_t RegisterAlarm( const ::Noob::Duration& duration,  AlarmCallback callback );
	int64_t RegisterAlarm( const ::Noob::TimePoint& timePoint,  AlarmCallback callback );
	void UnRegisterAlarm( int64_t alarmIndex );

private:
	struct imple;
	::std::unique_ptr<imple> pImple;

	void onAlarm();
	friend Dispatcher;
};

}
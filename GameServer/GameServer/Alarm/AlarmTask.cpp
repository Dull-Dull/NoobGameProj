#include "PreCompiled.h"
#include "AlarmTask.h"

AlarmTask::AlarmTask( int64_t index, const ::Noob::TimePoint& invokeTime, AlarmCallback callBack )
	: m_index( index), m_invokeTime( invokeTime ), m_callback( callBack ) {}

void AlarmTask::OnAlarm()
{
	m_callback();
}
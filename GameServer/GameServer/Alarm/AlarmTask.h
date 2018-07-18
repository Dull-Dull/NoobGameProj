#pragma once

using AlarmCallback = ::std::function<void()>;

class AlarmTask : public ::Noob::RefCnt
{
public:
	AlarmTask( int64_t index, const ::Noob::TimePoint& invokeTime, AlarmCallback callBack );	
	void OnAlarm();

	int64_t GetIndex() { return m_index; }
	const ::Noob::TimePoint& GetInvokeTime(){ return m_invokeTime; }
	
private:
	int64_t m_index;
	::Noob::TimePoint m_invokeTime;
	AlarmCallback m_callback;
};

DECL_CLASS( AlarmTask );
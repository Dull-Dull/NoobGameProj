#pragma once

namespace Noob
{

class AlarmManager;

enum class E_TASK_TYPE
{
	ACCEPT,
	CONNECT,
	RECV,
	CLOSE,
	TICK,
};

class Dispatcher
{
public:
	Dispatcher( unsigned int threadCnt = 1 );
	~Dispatcher();
	
	void Push( E_TASK_TYPE workType, const ::Noob::RefCntPtr& obj );
	AlarmManager& GetAlarmManager();

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};

}
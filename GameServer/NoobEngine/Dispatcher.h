#pragma once

#include "AlarmManager.h"

namespace Noob
{

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

	unsigned int GetThreadCnt();
private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};

}
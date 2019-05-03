#include "PreCompiled.h"

#include "Dispatcher.h"
#include "AlarmManager.h"
#include <NoobBasic/TaskQueue.hpp>

namespace Noob
{

struct Dispatcher::imple
{
	struct Task
	{
		E_TASK_TYPE m_type;
		::Noob::RefCntPtr m_obj;
	};

	::Noob::TaskQueue<Task> m_taskQueue;

	::std::vector<HANDLE> m_threadHandleCon;
	::std::vector<DWORD> m_threadIdCon;

	AlarmManager manager;

	static DWORD WINAPI threadFunc( void* arg );
};

DWORD WINAPI Dispatcher::imple::threadFunc( void* arg )
{
	imple* pImple = static_cast<imple*>( arg );
	imple::Task* task = nullptr;

	while( true )
	{
		if( pImple->m_taskQueue.Pop( task ) == false )
			continue;

		if( task == nullptr )
			return 0;

		switch( task->m_type )
		{
		case E_TASK_TYPE::ACCEPT:

			break;
		case E_TASK_TYPE::CONNECT:

			break;
		case E_TASK_TYPE::RECV:

			break;
		case E_TASK_TYPE::CLOSE:

			break;
		case E_TASK_TYPE::TICK:

			break;
		}
	}

	return 0;
}

Dispatcher::Dispatcher( unsigned int threadCnt ) : pImple( ::std::make_unique<imple>() )
{
	for( unsigned int i = 0; i < threadCnt; ++i )
	{
		HANDLE threadHandle = NULL;
		DWORD threadId = 0;

		threadHandle = CreateThread( NULL, 0, imple::threadFunc, pImple.get(), 0, &threadId );
		if( threadHandle != NULL )
		{
			pImple->m_threadHandleCon.push_back( threadHandle );
			pImple->m_threadIdCon.push_back( threadId );
		}
	}
}

Dispatcher::~Dispatcher()
{
	for( size_t i = 0; i < pImple->m_threadHandleCon.size(); ++i )
		pImple->m_taskQueue.Push( nullptr );

	WaitForMultipleObjects( static_cast<DWORD>( pImple->m_threadHandleCon.size() ), &(pImple->m_threadHandleCon[0]), true, 500 );
}

void Dispatcher::Push( E_TASK_TYPE workType, const ::Noob::RefCntPtr& obj )
{
	imple::Task* task = new imple::Task;
	task->m_type = workType;
	task->m_obj = obj;

	pImple->m_taskQueue.Push( task );
}

AlarmManager& Dispatcher::GetAlarmManager()
{
	return pImple->manager;
}

}
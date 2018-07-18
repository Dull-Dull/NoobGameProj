#include "PreCompiled.h"
#include "AlarmManager.h"

#include "../Dispatcher/GameDispatcher.h"

const static ::Noob::Tick g_tickUnit = ::Noob::Second / 2;

struct AlarmManager::imple
{
	using TickQueue = ::Noob::TaskQueue<int>;

	GameDispatcher* m_dispatcher;
	TickQueue m_tickQueue;

	HANDLE m_genTickHandle;
	DWORD m_genTickId;
	static DWORD WINAPI genTick( void* );

	HANDLE m_genAlarmHandle;
	DWORD m_genAlarmId;
	static DWORD WINAPI genAlarm( void* );

	int64_t m_indexCount;

	::std::list<AlarmTaskPtr> m_alarmList;
	::std::unordered_map<int64_t, ::std::list<AlarmTaskPtr>::iterator> m_alarmMap;	
};

DWORD WINAPI AlarmManager::imple::genTick( void* arg )
{
	imple* pImple = static_cast<imple*>( arg );

	DWORD tickUnit = ::std::chrono::duration_cast< ::std::chrono::duration<DWORD, ::std::milli> >( ::Noob::Duration( g_tickUnit ) ).count();

	while( true )
	{
		Sleep( tickUnit );
		pImple->m_tickQueue.Push( nullptr );
	}
}

DWORD WINAPI AlarmManager::imple::genAlarm( void* arg )
{
	imple* pImple = static_cast<imple*>( arg );
	int* tempTask = nullptr;

	while( true )
	{
		pImple->m_tickQueue.Pop( tempTask, INFINITE );

		::Noob::TimePoint nowTime = ::Noob::GetNow();

		for( auto iter = pImple->m_alarmList.begin(); iter != pImple->m_alarmList.end();)
		{
			AlarmTaskPtr& alarmTask = *iter;
			if( nowTime <= alarmTask->GetInvokeTime() )
			{
				pImple->m_dispatcher->Push( E_GAME_TASK::ALARM, alarmTask.Get() );
				pImple->m_alarmMap.erase( alarmTask->GetIndex() );
				iter = pImple->m_alarmList.erase( iter );
				continue;
			}
			++iter;
		}
	}
}

AlarmManager::AlarmManager( GameDispatcher* dispatcher ) : pImple( new imple )
{
	pImple->m_dispatcher = dispatcher;
	pImple->m_indexCount = 0LL;

	pImple->m_genTickHandle = CreateThread( NULL, 0, pImple->genTick, pImple.get(), 0, &(pImple->m_genTickId) );
	pImple->m_genAlarmHandle = CreateThread( NULL, 0, pImple->genAlarm, pImple.get(), 0, &(pImple->m_genAlarmId) );
}

AlarmManager::~AlarmManager()
{

}

int64_t AlarmManager::RegisterAlarm( const ::Noob::Duration& duration, AlarmCallback callback )
{
	return RegisterAlarm( ::Noob::GetNow() + duration, callback );
}

int64_t AlarmManager::RegisterAlarm( const ::Noob::TimePoint& timePoint, AlarmCallback callback )
{
	auto alarmTask = new AlarmTask( pImple->m_indexCount, timePoint, callback );

	auto iter = pImple->m_alarmList.insert( pImple->m_alarmList.end(), alarmTask );
	pImple->m_alarmMap.emplace( alarmTask->GetIndex(), iter );

	return alarmTask->GetIndex();
}

void AlarmManager::UnRegisterAlarm( int64_t alarmIndex )
{
	auto iter = pImple->m_alarmMap.find( alarmIndex );

	if( iter != pImple->m_alarmMap.end() )
	{
		pImple->m_alarmList.erase( iter->second );
		pImple->m_alarmMap.erase( iter );
	}
}
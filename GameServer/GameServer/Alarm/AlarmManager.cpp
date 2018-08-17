#include "PreCompiled.h"
#include "AlarmManager.h"

#include "../GameDispatcher/GameDispatcher.h"

const static ::Noob::Tick g_tickUnit = ::Noob::Second / 2;

struct AlarmManager::imple
{
	HANDLE m_genTickHandle;
	DWORD m_genTickId;
	static DWORD WINAPI genTickThread( void* );

	int64_t m_indexCount;

	::std::list<AlarmTaskPtr> m_alarmList;
	::std::unordered_map<int64_t, ::std::list<AlarmTaskPtr>::iterator> m_alarmMap;	
};

DWORD WINAPI AlarmManager::imple::genTickThread( void* arg )
{
	imple* pImple = static_cast<imple*>( arg );

	DWORD tickUnit = ::std::chrono::duration_cast< ::std::chrono::duration<DWORD, ::std::milli> >( ::Noob::Duration( g_tickUnit ) ).count();

	while( true )
	{
		Sleep( tickUnit );
		::GameDispatcher::GetInstance()->Push( E_GAME_TASK::TICK, nullptr );
	}
}

AlarmManager::AlarmManager() : pImple( new imple )
{
	pImple->m_indexCount = 0LL;

	pImple->m_genTickHandle = CreateThread( NULL, 0, pImple->genTickThread, pImple.get(), 0, &(pImple->m_genTickId) );
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

void AlarmManager::onAlarm()
{
	::Noob::TimePoint nowTime = ::Noob::GetNow();

	for( auto iter = pImple->m_alarmList.begin(); iter != pImple->m_alarmList.end();)
	{
		AlarmTaskPtr& alarmTask = *iter;
		if( nowTime >= alarmTask->GetInvokeTime() )
		{
			alarmTask->OnAlarm();
			pImple->m_alarmMap.erase( alarmTask->GetIndex() );
			iter = pImple->m_alarmList.erase( iter );
			continue;
		}
		++iter;
	}
}
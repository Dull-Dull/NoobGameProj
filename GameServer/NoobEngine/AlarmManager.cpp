#include "PreCompiled.h"

#include "AlarmManager.h"
#include "Dispatcher.h"

#include <NoobBasic/Lock.h>

namespace Noob
{

const static ::Noob::Tick g_tickUnit = ::Noob::Second / 2;

class AlarmLock
{
public:
	AlarmLock( bool needLock ) : m_needLock( needLock ) {}
	void Enter()
	{
		if( m_needLock )
			m_lock.Enter();
	}
	void Leave()
	{
		if( m_needLock )
			m_lock.Leave();
	}

private:
	::Noob::Lock m_lock;
	bool m_needLock;

};

class TickGenerator : public Singletone< TickGenerator >
{
public:
	TickGenerator();	
	void RegisterDispatcher( ::Noob::Dispatcher* dispatcher );

private:
	static DWORD WINAPI genTickThread( void* );
	
	HANDLE m_tickThreadHandle;
	DWORD m_tickThreadId;
	::std::array<::Noob::Dispatcher*, 128> m_dispatchers;
	size_t m_dispatcherCnt;
};

TickGenerator::TickGenerator()
{
	m_dispatcherCnt = 0;
	m_tickThreadId = 0;
	m_tickThreadHandle = CreateThread( NULL, 0, genTickThread, this, 0, & m_tickThreadId );

	if( m_tickThreadHandle == NULL )
	{
		::Noob::Log( ::Noob::LOG_TYPE::ERROR, L"genTickThread Error", ::GetLastError() );
		assert( false );
	}
}

void TickGenerator::RegisterDispatcher( ::Noob::Dispatcher* dispatcher )
{
	m_dispatchers[ m_dispatcherCnt ] = dispatcher;
	++m_dispatcherCnt;
}

DWORD WINAPI TickGenerator::genTickThread( void* arg )
{
	TickGenerator* generator = static_cast<TickGenerator*>( arg );

	DWORD tickUnit = ::std::chrono::duration_cast< ::std::chrono::duration<DWORD, ::std::milli> >( ::Noob::Duration( g_tickUnit ) ).count();

	while( true )
	{
		Sleep( tickUnit );
		for( size_t i = 0 ; i < generator->m_dispatcherCnt; ++i )
			generator->m_dispatchers[i]->Push( E_TASK_TYPE::TICK, nullptr );
	}
}

struct AlarmManager::imple
{
	int64_t m_indexCount;

	::std::list<AlarmTaskPtr> m_alarmList;
	::std::unordered_map<int64_t, ::std::list<AlarmTaskPtr>::iterator> m_alarmMap;
};

AlarmManager::AlarmManager( Dispatcher* dispatcher ) : pImple( new imple )
{
	pImple->m_indexCount = 0LL;
	TickGenerator::GetInstance()->RegisterDispatcher( dispatcher );
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
	auto alarmTask = new AlarmTask( pImple->m_indexCount++, timePoint, callback );
	int64_t alarmIndex = 0;

	auto iter = pImple->m_alarmList.insert(pImple->m_alarmList.end(), alarmTask);
	pImple->m_alarmMap.emplace(alarmTask->GetIndex(), iter);
	alarmIndex = alarmTask->GetIndex();

	return alarmIndex;
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

}
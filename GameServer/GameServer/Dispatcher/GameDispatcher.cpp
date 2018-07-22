#include "PreCompiled.h"
#include "GameDispatcher.h"

#include "../Player/Player.h"
#include "../Player/PlayerContainer.h"
#include "../Session/ClientSession.h"
#include "../Alarm/AlarmManager.h"

struct GameDispatcher::imple
{
	::Noob::TaskQueue<GameTask> m_taskQueue;
	HANDLE m_threadHandle;
	HANDLE m_tickGenThreadHandle;
	DWORD m_threadId;

	imple()
	{
		m_threadHandle = NULL;
		m_threadId = 0;
	}

	static DWORD WINAPI ThreadFunc( void* arg );
	void Accept( const ::Noob::RefCntPtr& obj );
	void Connect( const Noob::RefCntPtr& obj );
	void Recv( const Noob::RefCntPtr& obj );
	void Close( const Noob::RefCntPtr& obj );
	void Tick( const Noob::RefCntPtr& obj );
};

DWORD WINAPI GameDispatcher::imple::ThreadFunc( void* arg )
{
	imple* pImple = static_cast< imple* >( arg );
	GameTask* task = nullptr;

	while( true )
	{
		if( pImple->m_taskQueue.Pop( task, INFINITE ) == false )
			continue;

		if( task == nullptr )
			return 0;

		switch( task->m_eTask )
		{
		case E_GAME_TASK::ACCEPT:
			pImple->Accept( task->m_obj );
			break;
		case E_GAME_TASK::CONNECT:
			pImple->Connect( task->m_obj );
			break;
		case E_GAME_TASK::RECV:
			pImple->Recv( task->m_obj );
			break;
		case E_GAME_TASK::CLOSE:
			pImple->Close( task->m_obj );
			break;
		case E_GAME_TASK::TICK:
			pImple->Tick( task->m_obj );
			break;
		}

		delete task;
		task = nullptr;
	}

	return 0;
}

void GameDispatcher::imple::Accept( const Noob::RefCntPtr& obj )
{
	auto session = ::Noob::PtrCast<ClientSession>( obj );
	PlayerPtr player = new Player( session.Get() );
	session->SetPlayer( player.Get() );

	PlayerContainer::GetInstance()->Insert( player );
	
	player->OnAccept();
}

void GameDispatcher::imple::Connect( const Noob::RefCntPtr& obj )
{
	
}

void GameDispatcher::imple::Recv( const Noob::RefCntPtr& obj )
{
	auto session = ::Noob::PtrCast<ClientSession>( obj );
	auto pck = session->PopPck();
	auto player = session->GetPlayer();
	player->OnRecv( pck );
}

void GameDispatcher::imple::Close( const Noob::RefCntPtr& obj )
{
	auto session = ::Noob::PtrCast<ClientSession>( obj );
	auto player = session->GetPlayer();
	player->OnClose();

	PlayerContainer::GetInstance()->Delete( player );
}

void GameDispatcher::imple::Tick( const Noob::RefCntPtr& obj )
{
	::AlarmManager::GetInstance()->onAlarm();
}

GameDispatcher::GameDispatcher() : pImple( new imple )
{
	pImple->m_threadHandle = CreateThread( NULL, 0, pImple->ThreadFunc, pImple.get(), 0, &(pImple->m_threadId)  );
}

GameDispatcher::~GameDispatcher()
{
	pImple->m_taskQueue.Push( nullptr );
	WaitForSingleObject( pImple->m_threadHandle, 1000 );
}

void GameDispatcher::Push( E_GAME_TASK eTask, const ::Noob::RefCntPtr& obj )
{
	GameTask* task = new GameTask;
	task->m_eTask = eTask;
	task->m_obj = obj;

	pImple->m_taskQueue.Push( task );
}
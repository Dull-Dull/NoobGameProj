#include "PreCompiled.h"
#include "GameDispatcher.h"

#include "../Player/Player.h"

struct GameDispatcher::imple
{
	::Noob::TaskQueue<GameTask> m_taskQueue;
	HANDLE m_threadHandle;
	DWORD m_threadId;

	imple()
	{
		m_threadHandle = NULL;
		m_threadId = 0;
	}

	static DWORD WINAPI ThreadFunc( void* arg );
	void AcceptProc( const ::Noob::RefCntPtr& obj );
	void ConnectProc( const Noob::RefCntPtr& obj );
	void RecvProc( const Noob::RefCntPtr& obj );
	void CloseProc( const Noob::RefCntPtr& obj );
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
			pImple->AcceptProc( task->m_obj );
			break;
		case E_GAME_TASK::CONNECT:
			pImple->ConnectProc( task->m_obj );
			break;
		case E_GAME_TASK::RECV:
			pImple->RecvProc( task->m_obj );
			break;
		case E_GAME_TASK::CLOSE:
			pImple->CloseProc( task->m_obj );
			break;
		}

		delete task;
		task = nullptr;
	}

	return 0;
}

void GameDispatcher::imple::AcceptProc( const Noob::RefCntPtr& obj )
{
	
}

void GameDispatcher::imple::ConnectProc( const Noob::RefCntPtr& obj )
{

}

void GameDispatcher::imple::RecvProc( const Noob::RefCntPtr& obj )
{

}

void GameDispatcher::imple::CloseProc( const Noob::RefCntPtr& obj )
{

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
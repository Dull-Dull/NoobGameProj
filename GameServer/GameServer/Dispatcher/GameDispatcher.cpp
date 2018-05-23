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
	void AcceptProc( ::Noob::RefCnt& obj );
	void ConnectProc( ::Noob::RefCnt& obj );
	void RecvProc( ::Noob::RefCnt& obj );
	void CloseProc( ::Noob::RefCnt& obj );
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
	}

	return 0;
}

void GameDispatcher::imple::AcceptProc( ::Noob::RefCnt& obj )
{

}

void GameDispatcher::imple::ConnectProc( ::Noob::RefCnt& obj )
{

}

void GameDispatcher::imple::RecvProc( ::Noob::RefCnt& obj )
{

}

void GameDispatcher::imple::CloseProc( ::Noob::RefCnt& obj )
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

void GameDispatcher::Push( E_GAME_TASK eTask, const ::Noob::RefCnt& obj )
{
	GameTask* task = new GameTask;
	task->m_eTask = eTask;
	task->m_obj = obj;

	pImple->m_taskQueue.Push( task );
}
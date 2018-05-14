#pragma once

namespace Noob
{

class Lock
{
public:
	Lock()
	{
		InitializeCriticalSection( &m_cs );
	}

	~Lock()
	{
		DeleteCriticalSection( &m_cs );
	}

	void Enter()
	{
		EnterCriticalSection( &m_cs );
	}

	void Leave()
	{
		LeaveCriticalSection( &m_cs );
	}

private:
	CRITICAL_SECTION m_cs;
};

class LockGuard
{
public:
	LockGuard( Lock& lock ) : m_lock( lock )
	{
		m_lock.Enter();
	}

	~LockGuard()
	{
		m_lock.Leave();
	}
private:
	Lock& m_lock;
};

}
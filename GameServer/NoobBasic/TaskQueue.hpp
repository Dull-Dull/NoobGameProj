#pragma once
#include <Windows.h>

namespace Noob
{

template< typename Type >
class TaskQueue
{
public:
	TaskQueue( unsigned int numberOfProcess = 0 );
	~TaskQueue();

	void Push( Type* task );
	bool Pop( Type*& task, unsigned int milliSec = INFINITE );

private:

	HANDLE hIocp;
};

template< typename Type >
inline TaskQueue<Type>::TaskQueue( unsigned int numberOfProcess )
{
	DWORD dwNumberOfProcess = static_cast<DWORD>( numberOfProcess );
	hIocp = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, numberOfProcess );

	assert( hIocp );
}

template< typename Type >
inline TaskQueue<Type>::~TaskQueue()
{
	Type* obj = nullptr;
	while (Pop( obj, 0 )){}

	if (hIocp != NULL)
	{
		BOOL ret = CloseHandle( hIocp );
		assert( ret );
	}
}

template< typename Type >
inline void TaskQueue<Type>::Push( Type* task )
{
	BOOL ret = PostQueuedCompletionStatus( hIocp, 0, reinterpret_cast<ULONG_PTR>(task), nullptr );

	assert( ret );
}

template< typename Type >
inline bool TaskQueue<Type>::Pop( Type*& task, unsigned int milliSec )
{
	DWORD rcvByte = 0;
	OVERLAPPED* overlapped = nullptr;

	BOOL success = GetQueuedCompletionStatus( hIocp, &rcvByte, reinterpret_cast<PULONG_PTR>( &task ),
		&overlapped, static_cast<DWORD>( milliSec ) );

	if (!success)
	{
		DWORD errCode = GetLastError();
		if (errCode == ERROR_ABANDONED_WAIT_0 || errCode == WAIT_TIMEOUT)
			return false;
		else
			printf( "%d\n", errCode );
			assert( false );
	}

	return true;
}

}
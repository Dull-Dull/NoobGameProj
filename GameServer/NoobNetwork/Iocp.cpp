#include "PreCompiled.h"

#include "Iocp.h"
#include "Overlapped.h"
#include "Acceptor.h"
#include "Connector.h"
#include "TcpSession.h"

#pragma warning( disable : 4800 )

namespace Noob
{

Iocp::Iocp()
	: iocpHandle( NULL )
{

}

Iocp::~Iocp()
{
}

void Iocp::Start( int threadNum )
{
	if( threadNum == 0 )
	{
		SYSTEM_INFO si = {};
		GetSystemInfo( &si );

		threadNum = si.dwNumberOfProcessors * 2;
	}

	iocpHandle		= ::CreateIoCompletionPort( INVALID_HANDLE_VALUE,
							0, 0, static_cast< DWORD >( threadNum ) );

	if( iocpHandle == NULL )
	{
		Log( LOG_TYPE::ERROR, L"CreateCompletionPort(Start) Error", WSAGetLastError() );
		exit( 1 );
	}

	for( int i = 0; i < threadNum; ++i )
	{
		HANDLE	threadHandle = NULL;
		DWORD	threadId = 0;

		threadHandle = CreateThread( NULL, 0, ThreadFunc, this, 0, &threadId );

		if( threadHandle == NULL )
			Log( LOG_TYPE::ERROR, L"CreateThread Error", WSAGetLastError() );

		threadHandleContainer.push_back( threadHandle );
		threadIdContainer.push_back( threadId );
	}
}

void Iocp::Stop()
{
	for( size_t i = 0; i < threadHandleContainer.size(); ++i )
	{
		BOOL ret = PostQueuedCompletionStatus( iocpHandle, 0, 0, nullptr );
		if( !ret )
		{
			Log( LOG_TYPE::ERROR, L"Iocp Off Error ", GetLastError() );
		}
	}

	WaitForMultipleObjects( static_cast< DWORD >( threadHandleContainer.size() ),
							&threadHandleContainer[0], true, 5000 );

	for( auto& threadHandle : threadHandleContainer )
		CloseHandle( threadHandle );

	threadHandleContainer.clear();
	threadIdContainer.clear();
}

void Iocp::Wait()
{
	if( threadHandleContainer.empty() == false )
		WaitForMultipleObjects( static_cast< DWORD >( threadHandleContainer.size() ),
								&threadHandleContainer[0], true, INFINITE );
}

void Iocp::Register( SOCKET sock )
{
	if( iocpHandle != NULL )
	{
		if( CreateIoCompletionPort( (HANDLE)sock, iocpHandle, NULL, 0 ) == NULL )
		{
			Log( LOG_TYPE::ERROR, L"CreateIoCompletionPort(Register) Error", GetLastError() );
		}
	}
}

DWORD WINAPI Iocp::ThreadFunc( void* arg )
{
	Iocp*			This			= static_cast< Iocp* >( arg );

	while( true )
	{
		DWORD			transferedLen	= 0;
		ULONG_PTR		completionKey	= 0;
		Overlapped*		overlapped		= nullptr;

		bool success = GetQueuedCompletionStatus( This->iocpHandle, &transferedLen, &completionKey,
			reinterpret_cast<LPOVERLAPPED*>( &overlapped ), INFINITE );

		if( overlapped == nullptr )
			return 0;

		switch( overlapped->ioType )
		{
		case Overlapped::IO_TYPE::RECV :
			reinterpret_cast<ITcpSession*>( overlapped->object.Get() )->
				OnRecvForIocp( success, static_cast< unsigned int >( transferedLen ) );
			break;
		case Overlapped::IO_TYPE::SEND :
			reinterpret_cast<ITcpSession*>( overlapped->object.Get() )->
				OnSendForIocp( success, static_cast< unsigned int >( transferedLen ) );
			break;
		case Overlapped::IO_TYPE::ACCEPT :
			reinterpret_cast<IAcceptor*>( overlapped->object.Get() )->
				OnAccept( success, static_cast< unsigned int >( transferedLen ) );
			break;
		case Overlapped::IO_TYPE::CONNECT :
			reinterpret_cast<IConnector*>( overlapped->object.Get() )->
				OnConnect( success, static_cast< unsigned int >( transferedLen ) );
			break;
		}
	}	
}

}
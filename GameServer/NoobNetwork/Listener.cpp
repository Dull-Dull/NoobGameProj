#include "PreCompiled.h"

#include "Listener.h"

namespace Noob
{

Listener::Listener( Iocp* iocp, const EndPoint& endPoint )
{
	m_sock = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED );
	if( m_sock == INVALID_SOCKET )
	{
		Log( LOG_TYPE::ERROR, L"WSASocket Error ", WSAGetLastError() );
		exit( 1 );
	}

	SOCKADDR_IN sockAddr;
	ZeroMemory( &sockAddr, sizeof( sockAddr ) );

	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = htonl( endPoint.m_ip );
	sockAddr.sin_port = htons( endPoint.m_port );

	if( bind( m_sock, (SOCKADDR*)&sockAddr, sizeof( sockAddr ) ) == SOCKET_ERROR )
	{
		Log( LOG_TYPE::ERROR, L"bind Error ", WSAGetLastError() );
		exit( 1 );
	}

	if( listen( m_sock, 5 ) == SOCKET_ERROR )
	{
		Log( LOG_TYPE::ERROR, L"listen Error ", WSAGetLastError() );
		exit( 1 );
	}

	iocp->Regist( m_sock );
}

Listener::~Listener()
{
	closesocket( m_sock );
}

}
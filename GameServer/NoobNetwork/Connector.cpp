#include "PreCompiled.h"

#include "Connector.h"
#include "TcpSession.h"

namespace Noob
{

void IConnector::Connect( Iocp* iocp, EndPoint endPoint )
{
	m_iocp = iocp;

	m_sock = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED );

	SOCKADDR_IN sockAddr = {};

	m_addr.sin_family = PF_INET;
	m_addr.sin_addr.s_addr = htonl( endPoint.m_ip );
	m_addr.sin_port = htons( endPoint.m_port );

	if( connect( m_sock, (SOCKADDR*)&m_addr, sizeof( m_addr ) ) == SOCKET_ERROR )
	{
		Log( LOG_TYPE::ERROR, L"connect Error ", WSAGetLastError() );
		return;
	}

	OnConnect( true, UINT_MAX );
}

void IConnector::AsyncConnect( Iocp* iocp, EndPoint endPoint )
{
	m_iocp = iocp;

	m_sock = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED );

	GUID guid = WSAID_CONNECTEX;
	DWORD bytes = 0;
	LPFN_CONNECTEX connectEx;

	if( SOCKET_ERROR == ::WSAIoctl( m_sock, SIO_GET_EXTENSION_FUNCTION_POINTER, (LPVOID)&guid, sizeof( guid ), (LPVOID)&connectEx, sizeof( connectEx ), &bytes, NULL, NULL ) )
	{
		Log( LOG_TYPE::ERROR, L"connect Error ", WSAGetLastError() );
		//Todo 俊矾 贸府
	}

	SOCKADDR_IN addrNull = {};
	addrNull.sin_family = AF_INET;
	if( SOCKET_ERROR == bind( m_sock, (SOCKADDR*)&addrNull, sizeof( addrNull ) ) )
	{
		Log( LOG_TYPE::ERROR, L"connect Error ", WSAGetLastError() );
		//Todo 俊矾 贸府
	}

	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = htonl( endPoint.m_ip );
	m_addr.sin_port = htons( endPoint.m_port );

	m_overlapped.object = this;
	if( SOCKET_ERROR == connectEx( m_sock, (SOCKADDR*)&m_addr, sizeof( m_addr ), NULL, 0, NULL, &m_overlapped ) )
	{
		Log( LOG_TYPE::ERROR, L"connect Error ", WSAGetLastError() );
		m_overlapped.object = nullptr;
		//Todo 俊矾 贸府
	}
}

void IConnector::onConnectSession( ITcpSession* session )
{
	session->OnConnect();
	m_overlapped.object = nullptr;
}

}
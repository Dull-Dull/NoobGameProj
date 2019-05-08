#include "PreCompiled.h"
#include "Acceptor.h"
#include "Iocp.h"
#include "TcpSession.h"

namespace Noob
{

IAcceptor::IAcceptor( Iocp* iocp, Listener* listener )
	: m_iocp( iocp ), m_listener( listener ), m_overlapped( Overlapped::IO_TYPE::ACCEPT, this )
{
	
}

IAcceptor::~IAcceptor()
{

}

void IAcceptor::Post()
{
	m_sock = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED );
	
	m_overlapped.Init();
	ZeroMemory( m_buff, sizeof( m_buff ) );
	m_recvLen = 0;

	if(	AcceptEx( m_listener->GetSocket(), m_sock, m_buff, 0,
		sizeof( SOCKADDR_IN ) + 16, sizeof( SOCKADDR_IN ) + 16, &m_recvLen,
		( LPOVERLAPPED )&( m_overlapped ) )
		== false )
	{
		auto errorCode = WSAGetLastError();
		if( errorCode != WSA_IO_PENDING )
			Log( LOG_TYPE::ERROR, L"AcceptEx Error ", errorCode );
	}
}

void IAcceptor::getAddrInfo( EndPoint& local, EndPoint& remote )
{
	SOCKADDR_IN* localAddr = nullptr;
	int localSockLen = 0;
	SOCKADDR_IN* remoteAddr = nullptr;
	int remoteSockLen = 0;

	GetAcceptExSockaddrs(
		m_buff,
		0,
		sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		(SOCKADDR**)&localAddr,
		&localSockLen,
		(SOCKADDR**)&remoteAddr,
		&remoteSockLen
	);

	local.m_ip = localAddr->sin_addr.s_addr;
	local.m_port = localAddr->sin_port;

	remote.m_ip = remoteAddr->sin_addr.s_addr;
	remote.m_port = remoteAddr->sin_port;
}

void IAcceptor::onAcceptSession( ITcpSession* session )
{
	session->OnAccept();
	session->PostRecv();
}

}
#pragma once

#include "Iocp.h"
#include "EndPoint.h"
#include "Overlapped.h"

namespace Noob
{

class ITcpSession;

class IConnector : public RefCnt
{
public:
	IConnector()
		: m_sock( NULL ), m_addr{}, m_overlapped( Overlapped::IO_TYPE::CONNECT, this )
	{}
	virtual ~IConnector(){}

	void Connect( Iocp* iocp, EndPoint endPoint );
	void AsyncConnect( Iocp* iocp, EndPoint endPoint );

protected:
	virtual void OnConnect( bool success, unsigned int transferedLen ) = 0;
	void onConnectSession( ITcpSession* session );

	SOCKET m_sock;
	Iocp* m_iocp;
	Overlapped m_overlapped;
private:
	SOCKADDR_IN m_addr;

	friend Iocp;
};

template< class SessionType >
class Connector : public IConnector
{
public:
	Connector() : IConnector(){}
	~Connector(){}

protected:
	void OnConnect( bool success, unsigned int transferedLen ) override
	{
		if( success == false )
		{
			Log( LOG_TYPE::ERROR, L"Async Connect Fail ", WSAGetLastError() );
			m_overlapped.object = nullptr;
			return;
		}

		SessionType* session = new SessionType();
		session->Init( m_iocp, m_sock, EndPoint(), EndPoint() );
		onConnectSession( session );
	}
};

}
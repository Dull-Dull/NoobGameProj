#pragma once

#include "Iocp.h"
#include "EndPoint.h"
#include "Overlapped.h"

namespace Noob
{

class ITcpSession;

class IConnector
{
public:
	IConnector()
		: m_sock( NULL ), m_addr{}, m_overlapped( Overlapped::IO_TYPE::CONNECT, this )
	{}
	virtual ~IConnector(){}

	void Connect( Iocp* iocp, EndPoint endPoint );
	void AsyncConnect( Iocp* iocp, EndPoint endPoint );

protected:
	virtual void OnConnect() = 0;
	void onConnectSession( ITcpSession* session );

	SOCKET m_sock;
	Iocp* m_iocp;
private:
	SOCKADDR_IN m_addr;
	Overlapped m_overlapped;

	friend Iocp;
};

template< class SessionType >
class Connector : public IConnector
{
public:
	Connector() : IConnector(){}
	~Connector(){}

protected:
	void OnConnect() override
	{
		SessionType* session = new SessionType();
		session->Init( m_iocp, m_sock, EndPoint(), EndPoint() );
		onConnectSession( session );
	}
};

}
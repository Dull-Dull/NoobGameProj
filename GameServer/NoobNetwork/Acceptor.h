#pragma once

#include "Listener.h"
#include "Overlapped.h"

namespace Noob
{

class ITcpSession;

class IAcceptor
{
public:
	IAcceptor( Iocp* iocp, Listener* listener );
	virtual ~IAcceptor();

	void Post();
	virtual void OnAccept() = 0;

protected:
	Iocp* m_iocp;
	SOCKET m_sock;
private:
	Listener* m_listener;
	Overlapped m_overlapped;
	byte m_buff[1024];
	DWORD m_recvLen;

protected:
	void getAddrInfo( EndPoint& local, EndPoint& remote );
	void onAcceptSession( ITcpSession* session );
};

template< class SessionType >
class Acceptor : public IAcceptor
{
public:
	Acceptor( Iocp* iocp, Listener* listener )
		: IAcceptor( iocp, listener )
	{
	}

	virtual ~Acceptor()
	{

	}

	void OnAccept()
	{
		EndPoint local;
		EndPoint remote;

		getAddrInfo( local, remote );

		SessionType* session = new SessionType();
		session->Init( m_iocp, m_sock, local, remote );
		onAcceptSession( session );
	}
};

}
#pragma once

#include "TcpSession.h"
#include <NoobNetwork/Connector.h>

namespace Noob
{

template< class UserType, class DispatcherSelector >
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

	void OnAccept( bool success, unsigned int transferedLen ) override
	{
		if( success == false )
		{
			Log( LOG_TYPE::ERROR, L"Acceptor Closed ", WSAGetLastError() );
			m_overlapped.object = nullptr;
			return;
		}

		EndPoint local;
		EndPoint remote;

		getAddrInfo( local, remote );

		TcpSession* session = new TcpSession;
		session->Init( m_iocp, m_sock, local, remote );
		session->OnAccept( new UserType( session, DispatcherSelector::GetInstance()->Get() ) );
		session->PostRecv();
		Post();
	}
};

}
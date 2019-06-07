#pragma once

#include "TcpSession.h"
#include <NoobNetwork/Connector.h>

namespace Noob
{

template< class UserType, class DispatcherSelector >
class Connector : public IConnector
{
public:
	Connector() : IConnector(){}
	Connector(const Connector&) = delete;
	~Connector(){}

protected:
	void OnConnect( bool success, unsigned int transferedLen ) override
	{
		if( success == false )
		{
			Log( LOG_TYPE::ERROR, L"Connect Fail ", WSAGetLastError() );
			m_overlapped.object = nullptr;
			return;
		}

		TcpSession* session = new TcpSession;
		session->Init( m_iocp, m_sock, EndPoint(), EndPoint() );
		session->OnConnect( new UserType( session, DispatcherSelector::GetInstance()->Get() ) );
		session->PostRecv();
		m_overlapped.object = nullptr;
	}
};

}
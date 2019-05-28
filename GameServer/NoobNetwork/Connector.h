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
		: m_sock( NULL ), m_addr{}, m_overlapped( Overlapped::IO_TYPE::CONNECT, nullptr )
	{}
	virtual ~IConnector(){}

	void Connect( Iocp* iocp, EndPoint endPoint );
	void AsyncConnect( Iocp* iocp, EndPoint endPoint );

protected:
	virtual void OnConnect( bool success, unsigned int transferedLen ) = 0;

	SOCKET m_sock;
	Iocp* m_iocp;
	Overlapped m_overlapped;
private:
	SOCKADDR_IN m_addr;

	friend Iocp;
};

}
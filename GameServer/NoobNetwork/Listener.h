#pragma once

#include "Iocp.h"
#include "EndPoint.h"

namespace Noob
{

class Listener
{
public:
	Listener( Iocp* iocp, const EndPoint& endPoint );
	~Listener();

	SOCKET GetSocket() { return m_sock; }
	const EndPoint& GetEndPoint(){ return m_endPoint; }
private:
	SOCKET m_sock;
	EndPoint m_endPoint;
};

}

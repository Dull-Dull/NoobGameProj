#include "PreCompiled.h"

#include "Session/ClientSession.h"
#include "Session/ClientAcceptor.h"
#include "Dispatcher\GameDispatcher.h"
#include <GamePacket/PcksRegistration.h>

int main()
{
	::Noob::WinSockInitor initor;
	::Noob::IocpPtr iocp = new ::Noob::Iocp;
	
	iocp->Start();

	GameDispatcher dispatcher;
	ClientAcceptorManager acceptorManager( iocp.Get(), 15000, &dispatcher );	
	
	iocp->Wait();

	return 0;
}
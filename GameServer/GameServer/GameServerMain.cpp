#include "PreCompiled.h"

#include "Session/ClientSession.h"
#include "Session/ClientAcceptor.h"
#include "GameDispatcher/GameDispatcher.h"
#include <GamePacket/PcksRegistration.h>

int main()
{
	::Noob::MiniDump dump;

	::Noob::WinSockInitor initor;
	::Noob::IocpPtr iocp = new ::Noob::Iocp;
	
	iocp->Start();

	ClientAcceptorManager acceptorManager( iocp.Get(), 15000 );
	
	iocp->Wait();

	return 0;
}
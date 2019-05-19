#include "PreCompiled.h"

#include "Player/PlayerAcceptManager.h"
#include <GamePacket/PcksRegistration.h>

int main()
{
	::Noob::MiniDump dump;

	::Noob::WinSockInitor initor;
	::Noob::IocpPtr iocp = new ::Noob::Iocp;
	
	iocp->Start();

	PlayerAcceptManager acceptorManager( iocp.Get(), 15000 );
	
	iocp->Wait();

	return 0;
}
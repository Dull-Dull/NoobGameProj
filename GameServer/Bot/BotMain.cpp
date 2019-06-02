#include "PreCompiled.h"

#include "BotConnectManager.h"
#include <GamePacket/PcksRegistration.h>

int main()
{
	::Noob::MiniDump dump;

	::Noob::WinSockInitor initor;
	::Noob::IocpPtr iocp = new ::Noob::Iocp;

	iocp->Start();

	BotConnectManager::Connect( iocp.Get(), ::Noob::EndPoint( L"127.0.0.1", 15000 ), 80 );

	iocp->Wait();

	return 0;
}
#include "PreCompiled.h"

#include "ClientSession.h"
#include <GamePacket/PcksRegistration.h>

int main()
{
	WSADATA wsadata = {};
	WSAStartup( MAKEWORD( 2,2 ) , &wsadata );

	::Noob::Iocp iocp;
	iocp.Start();

	Noob::Listener listener( &iocp, Noob::EndPoint( INADDR_ANY, 15000 ) );
	Noob::Acceptor< ClientSession > acceptor( &iocp, &listener );

	acceptor.Post();

	iocp.Wait();

	WSACleanup();
	return 0;
}
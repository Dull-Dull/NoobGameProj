#include "PreCompiled.h"

#include "Session/ClientSession.h"
#include "Dispatcher\GameDispatcher.h"
#include <GamePacket/PcksRegistration.h>

int main()
{
	WSADATA wsadata = {};
	WSAStartup( MAKEWORD( 2,2 ) , &wsadata );

	::Noob::Iocp iocp;
	iocp.Start();

	Noob::Listener listener( &iocp, Noob::EndPoint( INADDR_ANY, 15000 ) );

	GameDispatcher dispatcher;
	::std::vector<ClientAcceptor*> acceptorContainer;
	for( int i = 0 ; i < 10 ; ++i )
		acceptorContainer.push_back( new ClientAcceptor( &dispatcher ) );

	Noob::Acceptor< ClientSession > acceptor( &iocp, &listener );
	acceptor.Post();

	iocp.Wait();
	WSACleanup();
	return 0;
}
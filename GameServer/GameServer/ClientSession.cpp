#include "PreCompiled.h"

#include "ClientSession.h"
#include <GamePacket\Packets\TestPcks.h>

ClientSession::ClientSession()
{

}

ClientSession::~ClientSession()
{

}

void ClientSession::OnAccept( ::Noob::IAcceptor* acceptor )
{
	acceptor->Post();
	printf("Accept Success!!\n");

	TestPck1 pck;
	pck.val1 = 1;
	pck.val2 = 2;
	pck.val3 = 3;
	pck.list.push_back( 1 );
	pck.list.push_back( 2 );
	pck.list.push_back( 3 );

	Send( pck );
}

void ClientSession::OnRecv( ::Noob::PacketPtr pck )
{
	printf("RecvPck %d\n", pck->index );
}

void ClientSession::OnClose()
{
	printf("Disconnect!!\n");
}
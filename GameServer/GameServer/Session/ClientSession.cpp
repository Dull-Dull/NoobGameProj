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
	
}

void ClientSession::OnRecv( ::Noob::PacketPtr pck )
{
	printf("RecvPck %d\n", pck->index );
}

void ClientSession::OnClose()
{
	printf("Disconnect!!\n");
}
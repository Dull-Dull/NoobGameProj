#include "PreCompiled.h"

#include "ClientSession.h"
#include "../Dispatcher/GameDispatcher.h"
#include <GamePacket\Packets\TestPcks.h>

ClientAcceptor::ClientAcceptor( ::Noob::Iocp* iocp, ::Noob::Listener* listener, GameDispatcher* dispatcher )
	: Acceptor<ClientSession>( iocp, listener ), m_dispatcher( dispatcher ){}

GameDispatcher* ClientAcceptor::GetDispatcher()
{
	return m_dispatcher;
}

struct ClientSession::imple
{
	Player* m_player;
	GameDispatcher* m_dispatcher;
};

ClientSession::ClientSession() : pImple( new imple )
{

}

ClientSession::~ClientSession()
{

}

void ClientSession::OnAccept( ::Noob::IAcceptor* acceptor )
{
	ClientAcceptor* clientAcceptor = static_cast<ClientAcceptor*>( acceptor );
	pImple->m_dispatcher = clientAcceptor->GetDispatcher();
	pImple->m_dispatcher->Push( E_GAME_TASK::ACCEPT, *this );

	acceptor->Post();
}

void ClientSession::OnRecv( ::Noob::PacketPtr pck )
{
	printf("RecvPck %d\n", pck->index );
}

void ClientSession::OnClose()
{
	pImple->m_dispatcher->Push( E_GAME_TASK::CLOSE, *this );
}

void ClientSession::SetPlayer( Player* player )
{
	pImple->m_player = player;
}

Player* ClientSession::GetPlayer()
{
	return pImple->m_player;
}
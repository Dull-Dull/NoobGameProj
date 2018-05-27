#include "PreCompiled.h"
#include "ClientSession.h"

#include "ClientAcceptor.h"
#include "../Dispatcher/GameDispatcher.h"
#include <GamePacket\Packets\TestPcks.h>
#include <concurrent_queue.h>

struct ClientSession::imple
{
	Player* m_player;
	GameDispatcher* m_dispatcher;
	::concurrency::concurrent_queue<::Noob::PacketPtr> m_pckQueue;
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
	pImple->m_dispatcher->Push( E_GAME_TASK::ACCEPT, this );

	acceptor->Post();
}

void ClientSession::OnRecv( ::Noob::PacketPtr pck )
{
	pImple->m_pckQueue.push( pck );
	pImple->m_dispatcher->Push( E_GAME_TASK::RECV, this );
}

void ClientSession::OnClose()
{
	pImple->m_dispatcher->Push( E_GAME_TASK::CLOSE, this );
}

void ClientSession::SetPlayer( Player* player )
{
	pImple->m_player = player;
}

Player* ClientSession::GetPlayer()
{
	return pImple->m_player;
}
#include "PreCompiled.h"
#include "ClientSession.h"

#include "ClientAcceptor.h"
#include "../GameDispatcher/GameDispatcher.h"
#include <concurrent_queue.h>

struct ClientSession::imple
{
	Player* m_player;
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
	GameDispatcher::GetInstance()->Push( E_GAME_TASK::ACCEPT, this );

	acceptor->Post();
}

void ClientSession::OnRecv( ::Noob::PacketPtr pck )
{
	pImple->m_pckQueue.push( pck );
	GameDispatcher::GetInstance()->Push( E_GAME_TASK::RECV, this );
}

void ClientSession::OnClose()
{
	GameDispatcher::GetInstance()->Push( E_GAME_TASK::CLOSE, this );
}

void ClientSession::SetPlayer( Player* player )
{
	pImple->m_player = player;
}

Player* ClientSession::GetPlayer()
{
	return pImple->m_player;
}

::Noob::PacketPtr ClientSession::PopPck()
{
	::Noob::PacketPtr pck = nullptr;
	pImple->m_pckQueue.try_pop( pck );
	return pck;
}
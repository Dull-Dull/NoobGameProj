#include "Precompiled.h"
#include "PlayerAcceptManager.h"
#include "Player.h"
#include <NoobEngine/TcpSessionAcceptor.h>
#include <NoobEngine/DispatcherSelector.h>

const static size_t g_AcceptorCnt = 10;

using PlayerAcceptor = ::Noob::Acceptor< Player, ::Noob::SingleThreadDispatcher >;
using PlayerAcceptorPtr = ::Noob::Ptr< PlayerAcceptor >;

struct PlayerAcceptManager::imple
{
	Noob::Listener listener;
	::std::vector< PlayerAcceptor* > acceptorCon;

	imple( ::Noob::Iocp* iocp, short port ) : listener( iocp, ::Noob::EndPoint( INADDR_ANY, port ) ){}
};

PlayerAcceptManager::PlayerAcceptManager( ::Noob::Iocp* iocp, short port ) : pImple( new imple( iocp, port ) )
{
	for( size_t i = 0; i < g_AcceptorCnt; ++i )
	{
		PlayerAcceptor* acceptor = new PlayerAcceptor( iocp, &( pImple->listener ) );
		acceptor->Post();
		pImple->acceptorCon.emplace_back( acceptor );
	}
}

PlayerAcceptManager::~PlayerAcceptManager()
{
}
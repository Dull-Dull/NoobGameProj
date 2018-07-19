#include "PreCompiled.h"
#include "ClientAcceptor.h"

#include "ClientSession.h"

struct ClientAcceptorManager::imple
{
	Noob::Listener listener;
	::std::vector< ClientAcceptorPtr > acceptorCon;

	imple( ::Noob::Iocp* iocp, short port ) : listener( iocp, ::Noob::EndPoint( INADDR_ANY, port ) )
	{}
};

ClientAcceptorManager::ClientAcceptorManager( ::Noob::Iocp* iocp, short port ) : pImple( new imple( iocp, port ) )
{
	for( size_t i = 0; i < g_AcceptorCnt; ++i )
	{
		ClientAcceptor* acceptor = new ClientAcceptor( iocp, &(pImple->listener) );
		acceptor->Post();
		pImple->acceptorCon.emplace_back( acceptor );
	}
}

ClientAcceptorManager::~ClientAcceptorManager()
{
}
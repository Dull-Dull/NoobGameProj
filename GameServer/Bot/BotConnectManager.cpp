#include "PreCompiled.h"
#include "BotConnectManager.h"

#include "Bot.h"
#include <NoobEngine/TcpSessionConnector.h>
#include <NoobEngine/DispatcherSelector.h>

void BotConnectManager::Connect( ::Noob::Iocp* iocp, ::Noob::EndPoint endPoint, size_t botCnt )
{
	using BotConnector = ::Noob::Connector<Bot, ::Noob::RRDispatcher>;

	for( size_t i = 0; i < botCnt; ++i )
	{
		BotConnector* connector = new BotConnector();
		connector->Connect( iocp, endPoint );
	}
}
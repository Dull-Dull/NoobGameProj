#include "PreCompiled.h"
#include "Bot.h"

#include "BotContainer.h"
#include <NoobEngine/TcpSession.h>
#include <NoobEngine/Dispatcher.h>
#include <NoobEngine/PacketDispatcher.h>

#include <GamePacket/Packets/Login.h>
#include <GamePacket/Packets/Game.h>

static ::std::atomic_uint g_idCount = 0;

Bot::Bot( ::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher ) : IUser( session, dispatcher)
{

}

void Bot::OnConnect()
{
	id = ::std::wstring( L"BOT_" ) + ::std::to_wstring( g_idCount++ );

	BotContainer::GetInstance()->Insert( this );

	CS_Hello hello;
	Send( hello );
}

void Bot::OnRecv( ::Noob::PacketPtr pck )
{
	::Noob::PacketDispatcher<Bot>::Call( this, pck );
}

void Bot::OnClose()
{
	BotContainer::GetInstance()->Delete( this );
}
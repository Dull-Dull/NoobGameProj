#include "PreCompiled.h"
#include "Bot.h"

#include <NoobEngine/PacketDispatcher.h>
#include <GamePacket/Packets/Login.h>
#include <GamePacket/Packets/Game.h>

#define BOT_PCK_PROC( PACKET ) REGISTER_PCK_PROC( Bot, PACKET )

BOT_PCK_PROC( SC_Hello )
void Bot::OnPacket( const SC_HelloPtr& pck )
{
	CS_Login login;
	login.nick = id;

	Send( login );
}
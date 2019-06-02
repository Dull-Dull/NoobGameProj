#include "PreCompiled.h"
#include "Bot.h"

#include <NoobEngine/PacketDispatcher.h>
#include <GamePacket/Packets/Login.h>
#include <GamePacket/Packets/Game.h>

#define BOT_PCK_PROC( PACKET ) REGISTER_PCK_PROC( Bot, PACKET )

BOT_PCK_PROC( SC_EnterPlayer )
void Bot::OnPacket( const SC_EnterPlayerPtr& pck )
{

}

BOT_PCK_PROC( N_Move )
void Bot::OnPacket( const N_MovePtr& pck )
{

}

BOT_PCK_PROC( N_Roll )
void Bot::OnPacket( const N_RollPtr& pck )
{

}

BOT_PCK_PROC( N_Chat )
void Bot::OnPacket( const N_ChatPtr& pck )
{

}
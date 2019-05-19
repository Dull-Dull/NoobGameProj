#include "PreCompiled.h"
#include "../Player.h"
#include "../PlayerContainer.h"
#include <NoobEngine/PacketDispatcher.h>

#include <GamePacket/Packets/Game.h>

#define PLAYER_PCK_PROC( PACKET ) REGISTER_PCK_PROC( Player, PACKET )

PLAYER_PCK_PROC( N_Move )
void Player::OnPacket( const N_MovePtr& pck )
{
	m_transform = pck->transform;
	m_animation = pck->animation;

  	float senderPing = ::Noob::TickToFloat( GetPing() );

	for( auto& player : *PlayerContainer::GetInstance() )
	{
		if( player->m_handShakeComplete == false || player.Get() == this )
			continue;

		float recverPing = ::Noob::TickToFloat( player->GetPing() );
		float interpolationTime = senderPing + recverPing;

		N_Move movePlayerPck;
		movePlayerPck.playerIndex = pck->playerIndex;
		movePlayerPck.transform.position = pck->transform.position + ( pck->transform.velocity * interpolationTime );
		movePlayerPck.transform.velocity = pck->transform.velocity;
		movePlayerPck.animation = pck->animation;

		player->Send( movePlayerPck );
	}
}

PLAYER_PCK_PROC(N_Roll)
void Player::OnPacket( const N_RollPtr& pck )
{
	float senderPing = ::Noob::TickToFloat( GetPing() );
	m_degree = pck->degree;

	for( auto& player : *PlayerContainer::GetInstance() )
	{
		if( player->m_handShakeComplete == false || player.Get() == this )
			continue;

		player->Send( *pck );
	}
}

PLAYER_PCK_PROC(N_Chat)
void Player::OnPacket( const N_ChatPtr& pck )
{
	for( auto& player : *PlayerContainer::GetInstance() )
	{
		if( player->m_handShakeComplete == false )
			continue;

		player->Send( *pck );
	}
}

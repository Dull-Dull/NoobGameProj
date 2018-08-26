#include "PreCompiled.h"
#include "../Player.h"
#include "../PlayerContainer.h"
#include "../Ping/PingManager.h"
#include "../../PacketDispatcher/PacketDispatcher.h"
#include <GamePacket/Packets/Game.h>

REGISTER_PCK_PROC(N_Move)
void Player::OnPacket( const N_MovePtr& pck )
{
	pck->playerIndex;

  	float senderPing = ::Noob::TickToFloat( m_ping->GetPing() );

	for( auto& player : *PlayerContainer::GetInstance() )
	{
		if( player->m_handShakeComplete == false || player.Get() == this )
			continue;

		float recverPing = ::Noob::TickToFloat( player->m_ping->GetPing() );
		float interpolationTime = senderPing + recverPing;

		N_Move movePlayerPck;
		movePlayerPck.playerIndex = pck->playerIndex;
		movePlayerPck.transform.position.x = 
			pck->transform.position.x + ( pck->transform.velocity.x * interpolationTime );

		movePlayerPck.transform.position.y = 
			pck->transform.position.y + ( pck->transform.velocity.y * interpolationTime );

		movePlayerPck.transform.velocity = pck->transform.velocity;
		movePlayerPck.animation = pck->animation;

		player->Send( movePlayerPck );
	}
}

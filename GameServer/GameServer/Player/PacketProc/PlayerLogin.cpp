#include "PreCompiled.h"
#include "../Player.h"
#include "../PlayerContainer.h"
#include "../Ping/PingManager.h"
#include "../../PacketDispatcher/PacketDispatcher.h"
#include <GamePacket/Packets/Login.h>
#include <GamePacket/Packets/Game.h>

unsigned int g_playerIndexCnt = 0;

::std::vector<Vector2D> g_spawnSpotList = {	{ 0.0f, 0.0f }, { -3.5f, 19.0f }, { -15.0f, 6.5f },
{ 16.0f, 11.0f }, { -25.0f, 0.0f }, { 23.0f, -5.0f },
{ 23.0f, -5.0f }, { 13.0f, -13.0f }, { 0.0f, -25.0f } };

REGISTER_PCK_PROC( CS_Hello )
void Player::OnPacket( const CS_HelloPtr& pck )
{
	SC_Hello hello;
	Send( hello );
	m_handShakeComplete = true;

	m_ping->SendPing();

	for( auto& player : *PlayerContainer::GetInstance() )
	{
		if( player->m_loginComplete == false || player.Get() == this )
			continue;

		SC_EnterPlayer enterPlayer;
		enterPlayer.playerIndex = player->m_index;
		enterPlayer.nick = player->m_nick;
		enterPlayer.transform = player->m_transform;
		enterPlayer.direction = player->m_direction;
		enterPlayer.animation = player->m_animation;

		Send( enterPlayer );
	}
}

REGISTER_PCK_PROC( CS_Login )
void Player::OnPacket( const CS_LoginPtr& loginReq )
{
	m_nick = loginReq->nick;
	m_index = g_playerIndexCnt++;
	m_loginComplete = true;
	m_transform.position = g_spawnSpotList[ ::Noob::Random::GetInteger( 0, 8 ) ];
	m_transform.velocity = { 0.0f ,0.0f };
	m_direction.direction = { 0.0f, 1.0f };
	m_direction.angularVelocity = 0.0f;
	m_animation.state = PLAYER_STATE::STOP;

	SC_Login loginAck;
	loginAck.playerIndex = m_index;
	loginAck.spawnPosition = m_transform.position;

	Send( loginAck );

	SC_EnterPlayer enterPlayer;
	enterPlayer.playerIndex = m_index;
	enterPlayer.nick = m_nick;
	enterPlayer.transform = m_transform;
	enterPlayer.direction = m_direction;
	enterPlayer.animation = m_animation;

	for( auto& player : *PlayerContainer::GetInstance() )
	{
		if( player->m_handShakeComplete && player.Get() != this )
			player->Send( enterPlayer );
	}
}

REGISTER_PCK_PROC( CS_Ping )
void Player::OnPacket( const CS_PingPtr& pck )
{
	m_ping->RecvPing( pck->tick );
}
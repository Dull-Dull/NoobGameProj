#include "PreCompiled.h"
#include "../Player.h"
#include "../PlayerContainer.h"
#include "../Ping/PingManager.h"
#include "../../PacketDispatcher/PacketDispatcher.h"
#include <GamePacket/Packets/Login.h>

unsigned int g_playerIndexCnt = 0;

::std::vector<Vector2D> g_spawnSpotList = {	{ 0.0f, 0.0f }, { -3.5f, 19.0f }, { -15.0f, 6.5f },
{ 16.0f, 11.0f }, { -25.0f, 0.0f }, { 23.0f, -5.0f },
{ 23.0f, -5.0f }, { 13.0f, -13.0f }, { 0.0f, -25.0f } };

REGIST_PCK_PROC(CS_Hello)
void Player::OnPacket( const CS_HelloPtr& pck )
{
	SC_Hello hello;
	Send( hello );
	m_handShakeComplete = true;

	m_ping->SendPing();

	for( auto& player : *PlayerContainer::GetInstance() )
	{
		if( player->m_loginComplete == false )
			continue;

		SC_NewPlayer newPlayer;
		newPlayer.playerIndex = player->m_index;
		newPlayer.nick = player->m_nick;
		newPlayer.transform = player->m_transform;
		newPlayer.direction = player->m_direction;
		newPlayer.animation = player->m_animation;

		Send( newPlayer );
	}
}

REGIST_PCK_PROC( CS_Login )
void Player::OnPacket( const CS_LoginPtr& loginReq )
{
	m_nick = loginReq->nick;
	m_index = g_playerIndexCnt++;

	SC_Login loginAck;
	loginAck.playerIndex = m_index;
	loginAck.spawnPosition = g_spawnSpotList[ ::Noob::Random::GetInteger( 0, 8 ) ];

	Send( loginAck );

	SC_NewPlayer newPlayer;
	newPlayer.playerIndex = m_index;
	newPlayer.nick = m_nick;
	newPlayer.transform.position = loginAck.spawnPosition;
	newPlayer.transform.velocity = { 0.0f ,0.0f };
	newPlayer.direction.direction = { 0.0f, -1.0f };
	newPlayer.direction.angularVelocity = 0.0f;
	newPlayer.animation.state = PLAYER_STATE::STOP;


	for( auto& player : *PlayerContainer::GetInstance() )
	{
		if( player->m_handShakeComplete )
			player->Send( newPlayer );
	}
}

REGIST_PCK_PROC( CS_Ping )
void Player::OnPacket( const CS_PingPtr& pck )
{
	m_ping->RecvPing( pck->tick );
}
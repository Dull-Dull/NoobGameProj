#include "PreCompiled.h"
#include "../Player.h"

#include "../PlayerContainer.h"
#include <NoobEngine/PacketDispatcher.h>
#include <GamePacket/Packets/Login.h>
#include <GamePacket/Packets/Game.h>

#define PLAYER_PCK_PROC( PACKET ) REGISTER_PCK_PROC( Player, PACKET )

::std::vector<::Noob::Vector2D> g_spawnSpotList = {	{ 0.0f, 0.0f }, { -3.5f, 19.0f }, { -15.0f, 6.5f },
{ 16.0f, 11.0f }, { -25.0f, 0.0f }, { 23.0f, -5.0f },
{ 23.0f, -5.0f }, { 13.0f, -13.0f }, { 0.0f, -25.0f } };

PLAYER_PCK_PROC( CS_Hello )
void Player::OnPacket( const CS_HelloPtr& pck )
{
	SC_Hello hello;
	Send( hello );
	m_handShakeComplete = true;

	for( auto& player : *PlayerContainer::GetInstance() )
	{
		if( player->m_loginComplete == false || player.Get() == this )
			continue;

		SC_EnterPlayer enterPlayer;
		enterPlayer.playerIndex = player->m_index;
		enterPlayer.nick = player->m_nick;
		enterPlayer.transform = player->m_transform;
		enterPlayer.animation = player->m_animation;
		enterPlayer.degree = player->m_degree;

		Send( enterPlayer );
	}
}

PLAYER_PCK_PROC( CS_Login )
void Player::OnPacket( const CS_LoginPtr& loginReq )
{
#ifdef _DEBUG
	::Noob::Log(::Noob::LOG_TYPE::CONSOLE, L"User Login : ", loginReq->nick);
#endif
	m_nick = loginReq->nick;
	m_loginComplete = true;
	m_transform.position = g_spawnSpotList[ ::Noob::Random::GetInteger( 0, 8 ) ];
	m_transform.velocity = { 0.0f ,0.0f };
	m_animation.state = PLAYER_STATE::STOP;
	m_degree = 0.0f;

	SC_Login loginAck;
	loginAck.playerIndex = m_index;
	loginAck.spawnPosition = m_transform.position;

	Send( loginAck );

	SC_EnterPlayer enterPlayer;
	enterPlayer.playerIndex = m_index;
	enterPlayer.nick = m_nick;
	enterPlayer.transform = m_transform;
	enterPlayer.animation = m_animation;
	enterPlayer.degree = m_degree;

	for( auto& player : *PlayerContainer::GetInstance() )
	{
		if( player->m_handShakeComplete && player.Get() != this )
			player->Send( enterPlayer );
	}
}
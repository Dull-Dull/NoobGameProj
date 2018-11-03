#include "PreCompiled.h"
#include "Player.h"

#include "Ping/PingManager.h"
#include "PlayerContainer.h"
#include "../PacketDispatcher/PacketDispatcher.h"
#include "../Session/ClientSession.h"
#include "../Alarm/AlarmManager.h"
#include <GamePacket/Packets/Login.h>

unsigned int g_playerIndexCnt = 0;

Player::Player( ClientSession* session )
{
	m_session = session;
	m_ping = nullptr;
	m_handShakeComplete = false;
	m_loginComplete = false;
	m_index = g_playerIndexCnt++;
}

Player::~Player()
{

}

void Player::OnAccept()
{
	if( m_ping == nullptr )
		m_ping = new PingManager( this );
}

void Player::OnRecv( ::Noob::PacketPtr pck )
{
	if( m_handShakeComplete == false )
	{
		if( pck->index != CS_Hello::GetIndex() )
		{
			m_session->Close();
			return;
		}
	}

	PacketDispatcher::Call( this, pck );
}

void Player::OnClose()
{
	if( m_loginComplete )
	{
		SC_ExitPlayer exit;
		exit.playerIndex = m_index;
		for( auto player : *PlayerContainer::GetInstance() )
		{
			if( player->m_handShakeComplete && player.Get() != this )
				player->Send( exit );
		}
	}	

	m_session = nullptr;
	SAFE_DELETE( m_ping );
}

void Player::Close()
{
	m_session->Close();
}
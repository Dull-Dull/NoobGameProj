#include "PreCompiled.h"
#include "Player.h"

#include "Ping/PingManager.h"
#include "PlayerContainer.h"
#include "../PacketDispatcher/PacketDispatcher.h"
#include "../Session/ClientSession.h"
#include "../Alarm/AlarmManager.h"
#include <GamePacket/Packets/Login.h>



Player::Player( ClientSession* session )
{
	m_session = session;
	m_ping = nullptr;
	m_handShakeComplete = false;
	m_loginComplete = false;
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
	m_session = nullptr;
	SAFE_DELETE( m_ping );
}

void Player::Close()
{
	m_session->Close();
}
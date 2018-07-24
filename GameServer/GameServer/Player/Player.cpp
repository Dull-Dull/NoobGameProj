#include "PreCompiled.h"
#include "Player.h"

#include "Ping/PingManager.h"
#include "../Session/ClientSession.h"
#include "../PacketProc/PacketProc.h"
#include "../Alarm/AlarmManager.h"
#include <GamePacket/Packets/Login.h>

Player::Player( ClientSession* session )
{
	m_session = session;
	m_ping = new PingManager( this );
	m_bSaidHello = false;
}

Player::~Player()
{

}

void Player::OnAccept()
{
	
}

void Player::OnRecv( ::Noob::PacketPtr pck )
{
	if( m_bSaidHello )
	{
		if( pck->index != CS_Hello::GetIndex() )
		{
			m_session->Close();
			return;
		}
	}

	PacketProcManager::Call( this, pck );
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

REGIST_PCK_PROC(CS_Hello)
void Player::OnPacket( const CS_HelloPtr& pck )
{
	SC_Hello hello;
	Send( hello );
	m_bSaidHello = true;
	
	m_ping->SendPing();
}

REGIST_PCK_PROC( CS_Ping )
void Player::OnPacket( const CS_PingPtr& pck )
{
	m_ping->RecvPing( pck->tick );
}
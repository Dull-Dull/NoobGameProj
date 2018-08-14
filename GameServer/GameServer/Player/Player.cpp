#include "PreCompiled.h"
#include "Player.h"

#include "Ping/PingManager.h"
#include "../Session/ClientSession.h"
#include "../PacketProc/PacketProc.h"
#include "../Alarm/AlarmManager.h"
#include <GamePacket/Packets/Login.h>

unsigned int g_playerIndexCnt = 0;

Player::Player( ClientSession* session )
{
	m_session = session;
	m_ping = nullptr;
	m_saidHello = false;
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
	if( m_saidHello == false )
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
	m_saidHello = true;
	
	m_ping->SendPing();
}

REGIST_PCK_PROC( CS_Login )
void Player::OnPacket( const CS_LoginPtr& loginReq )
{
	m_nick = loginReq->nick;

	SC_Login loginAck;
	loginAck.playerIndex = g_playerIndexCnt++;
	loginAck.spawnPosition = ::Noob::Random::GetInteger(0, 8);

	Send( loginAck );
}

REGIST_PCK_PROC( CS_Ping )
void Player::OnPacket( const CS_PingPtr& pck )
{
	m_ping->RecvPing( pck->tick );
}
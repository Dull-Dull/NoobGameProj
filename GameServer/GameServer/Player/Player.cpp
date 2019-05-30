#include "PreCompiled.h"
#include "Player.h"

#include "PlayerContainer.h"
#include <NoobEngine/PacketDispatcher.h>
#include <GamePacket/Packets/Login.h>

unsigned int g_playerIndexCnt = 0;

Player::Player( ::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher )
	: ::Noob::IUser( session, dispatcher )
{
	m_handShakeComplete = false;
	m_loginComplete = false;
	m_index = g_playerIndexCnt++;
}

Player::~Player()
{

}

void Player::OnAccept()
{
	PlayerContainer::GetInstance()->Insert( this );
}

void Player::OnRecv( ::Noob::PacketPtr pck )
{
	if( m_handShakeComplete == false )
	{
		if( pck->index != CS_Hello::GetIndex() &&
			pck->index != Ping::GetIndex() )
		{
			Close();
			return;
		}
	}

	::Noob::PacketDispatcher<Player>::Call( this, pck );
}

void Player::OnClose()
{
	PlayerContainer::GetInstance()->Delete( this );

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
}
#include "PreCompiled.h"
#include "Player.h"

#include "../PacketProc/PacketProc.h"
#include <GamePacket/Packets/Login.h>
#include <GamePacket/Packets/TestPcks.h>

struct Player::imple
{
	ClientSession* m_session;
};

Player::Player( ClientSession* session ) : pImple( new imple )
{
	pImple->m_session = session;
}

Player::~Player()
{

}

void Player::OnAccept()
{

}

void Player::OnRecv( ::Noob::PacketPtr pck )
{
	PacketProcManager::Call( this, pck );
}

void Player::OnClose()
{
	pImple->m_session = nullptr;
}

REGIST_PCK_PROC(CS_Hello)
void Player::OnPacket( const CS_HelloPtr& pck )
{

}
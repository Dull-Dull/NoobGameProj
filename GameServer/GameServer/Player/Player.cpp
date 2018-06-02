#include "PreCompiled.h"
#include "Player.h"

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

}

void Player::OnClose()
{
	pImple->m_session = nullptr;
}
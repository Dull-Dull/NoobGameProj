#pragma once
#include "../Session/ClientSession.h"
#include <GamePacket\Datas\Reflection.h>

class PingManager;

class Player : public ::Noob::RefCnt
{
public:
	Player( ClientSession* session );
	~Player();
	
	void OnAccept();
	void OnRecv( ::Noob::PacketPtr pck );
	void OnClose();

	template< typename PacketType >
	void Send( PacketType& pck )
	{
		m_session->Send( pck );
	}

	void Close();

	template< class PacketType >
	void OnPacket( const ::Noob::Ptr<PacketType>& pck ){ static_assert( false, "Invalid Pck" ); }

	unsigned int GetIndex(){ return m_index; }

private:
	ClientSession* m_session;
	PingManager* m_ping;
	bool m_handShakeComplete;
	bool m_loginComplete;

	unsigned int m_index;
	::std::wstring m_nick;
	PlayerTransform m_transform;
	float m_degree;
	PlayerAnimation m_animation;
};

using PlayerPtr = ::Noob::Ptr<Player>;
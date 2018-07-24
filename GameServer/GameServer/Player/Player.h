#pragma once
#include "../Session/ClientSession.h"

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

private:
	ClientSession* m_session;
	PingManager* m_ping;
	bool m_bSaidHello;
};

using PlayerPtr = ::Noob::Ptr<Player>;
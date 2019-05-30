#pragma once
#include <NoobEngine/IUser.h>
#include <GamePacket/Datas/Reflection.h>

namespace Noob
{
DECL_CLASS( TcpSession );
class Dispatcher;
}

class Player : public ::Noob::IUser
{
public:
	Player( ::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher );
	~Player();
	
	void OnAccept() override;
	void OnRecv( ::Noob::PacketPtr pck ) override;
	void OnClose() override;

	template< class PacketType >
	void OnPacket( const ::Noob::Ptr<PacketType>& pck ){ static_assert( false, "Invalid Pck" ); }

	unsigned int GetIndex(){ return m_index; }

private:
	bool m_handShakeComplete;
	bool m_loginComplete;

	unsigned int m_index;
	::std::wstring m_nick;
	PlayerTransform m_transform;
	float m_degree;
	PlayerAnimation m_animation;
};

DECL_CLASS( Player );
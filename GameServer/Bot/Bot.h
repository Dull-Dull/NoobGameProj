#pragma once

#include <NoobEngine/IUser.h>
#include <GamePacket/Datas/Reflection.h>

namespace Noob
{
DECL_CLASS( TcpSession );
class Dispatcher;
}

class Bot : public ::Noob::IUser
{
public:
	Bot( ::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher );

	void OnConnect() override;
	void OnRecv( ::Noob::PacketPtr pck ) override;
	void OnClose() override;

	template< class PacketType >
	void OnPacket( const ::Noob::Ptr<PacketType>& pck ) { static_assert( false, "Invalid Pck" ); }
private:
	::std::wstring id;
};

DECL_CLASS( Bot );
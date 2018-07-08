#pragma once

class ClientSession;

class Player : public ::Noob::RefCnt
{
public:
	Player( ClientSession* session );
	~Player();
	
	void OnAccept();
	void OnRecv( ::Noob::PacketPtr pck );
	void OnClose();

	void Send( const ::Noob::PacketPtr pck );

	template< class PacketType >
	void OnPacket( const ::Noob::Ptr<PacketType>& pck );

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};

using PlayerPtr = ::Noob::Ptr<Player>;
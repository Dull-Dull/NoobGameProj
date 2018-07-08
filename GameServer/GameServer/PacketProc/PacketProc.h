#pragma once

DECL_CLASS( Player );
class PacketProcRegisterer;

class PacketProcManager
{
public:
	using Func = void (Player::*)( const ::Noob::PacketPtr& );
	static void Call( const ::Noob::PacketPtr& pck );
private:
	static ::std::unordered_map< unsigned int, Func >* m_pckProcCon;
	friend PacketProcRegisterer;
};

class PacketProcRegisterer
{
public:
	PacketProcRegisterer( unsigned int pckIndex, const PacketProcManager::Func& callbackFunc );
};

#define REGIST_PCK_PROC( PACKET_TYPE )\
DECL_STRUCT( PACKET_TYPE );\
template<> void Player::OnPacket< PACKET_TYPE >(const ::Noob::Ptr<PACKET_TYPE>&);\
PacketProcRegisterer __##PACKET_TYPE##Registerer( PACKET_TYPE::GetIndex(),\
reinterpret_cast<PacketProcManager::Func>( &Player::OnPacket<PACKET_TYPE> ) );\
template<>
#include "PreCompiled.h"
#include "PacketDispatcher.h"
#include "../Player/Player.h"

::std::unordered_map< unsigned int, PacketDispatcher::Func >* PacketDispatcher::m_pckProcCon = nullptr;

void PacketDispatcher::Call( Player* player, const ::Noob::PacketPtr& pck )
{
	auto iter = m_pckProcCon->find( pck->index );
	if( iter != m_pckProcCon->end() )
		(player->*(iter->second))( pck );
}

PacketProcRegisterer::PacketProcRegisterer( unsigned int pckIndex, PacketDispatcher::Func callbackFunc )
{
	if( PacketDispatcher::m_pckProcCon == nullptr )
		PacketDispatcher::m_pckProcCon = new ::std::unordered_map< unsigned int, PacketDispatcher::Func >();

	if( PacketDispatcher::m_pckProcCon->find( pckIndex ) != PacketDispatcher::m_pckProcCon->end() )
		assert( false );

	PacketDispatcher::m_pckProcCon->emplace( pckIndex, callbackFunc );
}
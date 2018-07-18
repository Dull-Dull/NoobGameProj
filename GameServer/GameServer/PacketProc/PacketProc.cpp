#include "PreCompiled.h"
#include "PacketProc.h"
#include "../Player/Player.h"

::std::unordered_map< unsigned int, PacketProcManager::Func >* PacketProcManager::m_pckProcCon = nullptr;

void PacketProcManager::Call( Player* player, const ::Noob::PacketPtr& pck )
{
	auto iter = m_pckProcCon->find( pck->index );
	if( iter != m_pckProcCon->end() )
		(player->*(iter->second))( pck );
}

PacketProcRegisterer::PacketProcRegisterer( unsigned int pckIndex, PacketProcManager::Func callbackFunc )
{
	if( PacketProcManager::m_pckProcCon == nullptr )
		PacketProcManager::m_pckProcCon = new ::std::unordered_map< unsigned int, PacketProcManager::Func >();

	if( PacketProcManager::m_pckProcCon->find( pckIndex ) == PacketProcManager::m_pckProcCon->end() )
		assert( false );

	PacketProcManager::m_pckProcCon->emplace( pckIndex, callbackFunc );
}
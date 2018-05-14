#include "PreCompiled.h"

#include "PacketFactory.h"

namespace Noob
{

PacketFuncContainer* PacketFactory::pckFuncCon = nullptr;

Packet * PacketFactory::CreatePacket( PacketHeader * header, char * buff )
{
	auto iter = pckFuncCon->find( header->index );
	
	if( iter == pckFuncCon->end() )
	{
		Log( LOG_TYPE::ERROR, L"CreatePacketFail", header->index );
		return nullptr;
	}

	StreamBuf streamBuff(reinterpret_cast<byte*>( buff ), header->length - sizeof( PacketHeader ) );	
	return (*iter).second( &streamBuff);
}

void PacketFactory::RegistPacket( unsigned int index, std::function<Packet*(StreamBuf*)> func )
{
	if( pckFuncCon == nullptr )
		pckFuncCon = new PacketFuncContainer;

	auto ret = pckFuncCon->emplace( index, func );
	assert( ret.second );
}

}
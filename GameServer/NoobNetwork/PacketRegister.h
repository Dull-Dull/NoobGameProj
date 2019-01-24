#pragma once

#include "Packet.h"

namespace Noob
{

class PacketRegister
{
public:
	PacketRegister( unsigned int index, ::std::function<Packet*(StreamBuf*)> func );
	~PacketRegister(){}
};

#define REGISTER_PACKET( PacketType )\
::Noob::PacketRegister __##PacketType##Register__( PacketType::GetIndex(), \
[]( StreamBuf* buff )-> ::Noob::Packet* { PacketType* pck = new PacketType;\
							StreamReader stream( *buff );\
							stream >> *pck;\
							return pck; }\
 );

}
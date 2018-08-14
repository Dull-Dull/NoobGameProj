#pragma once

#include "Packet.h"

namespace Noob
{

using PacketFuncContainer = ::std::unordered_map< unsigned int, ::std::function<Packet*(StreamBuf*)> >;

class PacketFactory
{
public:
	static Packet* CreatePacket( PacketHeader* header, char* buff );
	static void RegistPacket( unsigned int index, ::std::function<Packet*(StreamBuf*)> func );

private:
	static PacketFuncContainer* pckFuncCon;
};

}
#include "PreCompiled.h"
#include "PacketRegister.h"

#include "PacketFactory.h"

namespace Noob
{

PacketRegister::PacketRegister( unsigned int index, ::std::function<Packet*( StreamBuf* )> func )
{
	PacketFactory::RegistPacket( index, func );
}

}
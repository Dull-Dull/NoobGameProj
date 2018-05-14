#pragma once

namespace Noob
{

struct PacketHeader
{
	unsigned int length;
	unsigned int index;
};

struct Packet : public RefCnt
{
	unsigned int index;
	virtual std::wstring GetName() = 0;
};
using PacketPtr = Ptr< Packet >;

}
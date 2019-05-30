#pragma once

#include <NoobNetwork/Packet.h>

struct Ping : public ::Noob::Packet
{
	Ping()
	{
		index = 0;
	}

	::std::wstring GetName() { return L"Ping"; }
	static unsigned int GetIndex() { return 0; }
};

inline StreamReader& operator>>( StreamReader& stream, Ping& val )
{
	return stream;
}

inline StreamWriter& operator<<( StreamWriter& stream, Ping& val )
{
	return stream;
}

DECL_STRUCT( Ping );
#pragma once

#include "../Datas/Math.h"

struct SC_Hello : public ::Noob::Packet
{
	SC_Hello()
	{
		index = 1;
	}

	std::wstring GetName(){ return L"SC_Hello"; }
	static unsigned int GetIndex(){ return 1; }
};

inline StreamReader& operator>>( StreamReader& stream, SC_Hello& val )
{
	return stream;
}

inline StreamWriter& operator<<( StreamWriter& stream, SC_Hello& val )
{
	return stream;
}

struct CS_Hello : public ::Noob::Packet
{
	CS_Hello()
	{
		index = 2;
	}

	std::wstring GetName(){ return L"CS_Hello"; }
	static unsigned int GetIndex(){ return 2; }
};

inline StreamReader& operator>>( StreamReader& stream, CS_Hello& val )
{
	return stream;
}

inline StreamWriter& operator<<( StreamWriter& stream, CS_Hello& val )
{
	return stream;
}

struct CS_Login : public ::Noob::Packet
{
	::std::wstring Nick;

	CS_Login()
	{
		index = 3;
	}

	CS_Login( ::std::wstring _Nick )
	{
		index = 3;
		Nick = _Nick;
	}

	std::wstring GetName(){ return L"CS_Login"; }
	static unsigned int GetIndex(){ return 3; }
};

inline StreamReader& operator>>( StreamReader& stream, CS_Login& val )
{
	return stream>>val.Nick;
}

inline StreamWriter& operator<<( StreamWriter& stream, CS_Login& val )
{
	return stream<<val.Nick;
}

struct SC_Login : public ::Noob::Packet
{
	unsigned int PlayerIndex;
	Vector2D SpawnPosition;

	SC_Login()
	{
		index = 4;
	}

	SC_Login( unsigned int _PlayerIndex, Vector2D _SpawnPosition )
	{
		index = 4;
		PlayerIndex = _PlayerIndex;
		SpawnPosition = _SpawnPosition;
	}

	std::wstring GetName(){ return L"SC_Login"; }
	static unsigned int GetIndex(){ return 4; }
};

inline StreamReader& operator>>( StreamReader& stream, SC_Login& val )
{
	return stream>>val.PlayerIndex>>val.SpawnPosition;
}

inline StreamWriter& operator<<( StreamWriter& stream, SC_Login& val )
{
	return stream<<val.PlayerIndex<<val.SpawnPosition;
}

struct SC_Ping : public ::Noob::Packet
{
	int64_t Tick;

	SC_Ping()
	{
		index = 5;
	}

	SC_Ping( int64_t _Tick )
	{
		index = 5;
		Tick = _Tick;
	}

	std::wstring GetName(){ return L"SC_Ping"; }
	static unsigned int GetIndex(){ return 5; }
};

inline StreamReader& operator>>( StreamReader& stream, SC_Ping& val )
{
	return stream>>val.Tick;
}

inline StreamWriter& operator<<( StreamWriter& stream, SC_Ping& val )
{
	return stream<<val.Tick;
}

struct CS_Ping : public ::Noob::Packet
{
	int64_t Tick;

	CS_Ping()
	{
		index = 6;
	}

	CS_Ping( int64_t _Tick )
	{
		index = 6;
		Tick = _Tick;
	}

	std::wstring GetName(){ return L"CS_Ping"; }
	static unsigned int GetIndex(){ return 6; }
};

inline StreamReader& operator>>( StreamReader& stream, CS_Ping& val )
{
	return stream>>val.Tick;
}

inline StreamWriter& operator<<( StreamWriter& stream, CS_Ping& val )
{
	return stream<<val.Tick;
}

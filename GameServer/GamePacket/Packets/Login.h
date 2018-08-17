#pragma once

#include "../Datas/Math.h"

struct SC_Hello : public ::Noob::Packet
{
	SC_Hello()
	{
		index = 1;
	}

	::std::wstring GetName(){ return L"SC_Hello"; }
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

	::std::wstring GetName(){ return L"CS_Hello"; }
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
	::std::wstring nick;

	CS_Login()
	{
		index = 3;
	}

	CS_Login( ::std::wstring _nick )
	{
		index = 3;
		nick = _nick;
	}

	::std::wstring GetName(){ return L"CS_Login"; }
	static unsigned int GetIndex(){ return 3; }
};

inline StreamReader& operator>>( StreamReader& stream, CS_Login& val )
{
	return stream>>val.nick;
}

inline StreamWriter& operator<<( StreamWriter& stream, CS_Login& val )
{
	return stream<<val.nick;
}

struct SC_Login : public ::Noob::Packet
{
	unsigned int playerIndex;
	Vector2D spawnPosition;

	SC_Login()
	{
		index = 4;
	}

	SC_Login( unsigned int _playerIndex, Vector2D _spawnPosition )
	{
		index = 4;
		playerIndex = _playerIndex;
		spawnPosition = _spawnPosition;
	}

	::std::wstring GetName(){ return L"SC_Login"; }
	static unsigned int GetIndex(){ return 4; }
};

inline StreamReader& operator>>( StreamReader& stream, SC_Login& val )
{
	return stream>>val.playerIndex>>val.spawnPosition;
}

inline StreamWriter& operator<<( StreamWriter& stream, SC_Login& val )
{
	return stream<<val.playerIndex<<val.spawnPosition;
}

struct SC_NewPlayer : public ::Noob::Packet
{
	unsigned int playerIndex;
	::std::wstring nick;
	Vector2D position;

	SC_NewPlayer()
	{
		index = 5;
	}

	SC_NewPlayer( unsigned int _playerIndex, ::std::wstring _nick, Vector2D _position )
	{
		index = 5;
		playerIndex = _playerIndex;
		nick = _nick;
		position = _position;
	}

	::std::wstring GetName(){ return L"SC_NewPlayer"; }
	static unsigned int GetIndex(){ return 5; }
};

inline StreamReader& operator>>( StreamReader& stream, SC_NewPlayer& val )
{
	return stream>>val.playerIndex>>val.nick>>val.position;
}

inline StreamWriter& operator<<( StreamWriter& stream, SC_NewPlayer& val )
{
	return stream<<val.playerIndex<<val.nick<<val.position;
}

struct SC_Ping : public ::Noob::Packet
{
	int64_t tick;

	SC_Ping()
	{
		index = 6;
	}

	SC_Ping( int64_t _tick )
	{
		index = 6;
		tick = _tick;
	}

	::std::wstring GetName(){ return L"SC_Ping"; }
	static unsigned int GetIndex(){ return 6; }
};

inline StreamReader& operator>>( StreamReader& stream, SC_Ping& val )
{
	return stream>>val.tick;
}

inline StreamWriter& operator<<( StreamWriter& stream, SC_Ping& val )
{
	return stream<<val.tick;
}

struct CS_Ping : public ::Noob::Packet
{
	int64_t tick;

	CS_Ping()
	{
		index = 7;
	}

	CS_Ping( int64_t _tick )
	{
		index = 7;
		tick = _tick;
	}

	::std::wstring GetName(){ return L"CS_Ping"; }
	static unsigned int GetIndex(){ return 7; }
};

inline StreamReader& operator>>( StreamReader& stream, CS_Ping& val )
{
	return stream>>val.tick;
}

inline StreamWriter& operator<<( StreamWriter& stream, CS_Ping& val )
{
	return stream<<val.tick;
}

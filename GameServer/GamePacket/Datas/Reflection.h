#pragma once

#include "../Datas/Math.h"

enum class PLAYER_STATE : unsigned int
{
	STOP,
	RUN,
	__MAX__
};

inline StreamReader& operator>>( StreamReader& stream, PLAYER_STATE& val )
{
	return stream >> (unsigned int)val;
}
inline StreamWriter& operator<<( StreamWriter& stream, PLAYER_STATE& val )
{
	return stream << (unsigned int)val;
}

struct PlayerMove
{
	Vector2D position;
	Vector2D velocity;

	static ::std::wstring GetName(){ return L"PlayerMove"; }
};

inline StreamReader& operator>>( StreamReader& stream, PlayerMove& val )
{
	return stream>>val.position>>val.velocity;
}

inline StreamWriter& operator<<( StreamWriter& stream, PlayerMove& val )
{
	return stream<<val.position<<val.velocity;
}

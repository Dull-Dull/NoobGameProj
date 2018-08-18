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

struct PlayerTransform
{
	Vector2D position;
	Vector2D velocity;

	static ::std::wstring GetName(){ return L"PlayerTransform"; }
};

inline StreamReader& operator>>( StreamReader& stream, PlayerTransform& val )
{
	return stream>>val.position>>val.velocity;
}

inline StreamWriter& operator<<( StreamWriter& stream, PlayerTransform& val )
{
	return stream<<val.position<<val.velocity;
}

struct PlayerDirection
{
	Vector2D direction;
	float angularVelocity;

	static ::std::wstring GetName(){ return L"PlayerDirection"; }
};

inline StreamReader& operator>>( StreamReader& stream, PlayerDirection& val )
{
	return stream>>val.direction>>val.angularVelocity;
}

inline StreamWriter& operator<<( StreamWriter& stream, PlayerDirection& val )
{
	return stream<<val.direction<<val.angularVelocity;
}

struct PlayerAnimation
{
	PLAYER_STATE state;

	static ::std::wstring GetName(){ return L"PlayerAnimation"; }
};

inline StreamReader& operator>>( StreamReader& stream, PlayerAnimation& val )
{
	return stream>>val.state;
}

inline StreamWriter& operator<<( StreamWriter& stream, PlayerAnimation& val )
{
	return stream<<val.state;
}

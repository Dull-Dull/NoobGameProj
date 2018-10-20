#pragma once

#include "../Datas/Reflection.h"

struct N_Move : public ::Noob::Packet
{
	unsigned int playerIndex;
	PlayerTransform transform;
	PlayerAnimation animation;

	N_Move()
	{
		index = 101;
	}

	N_Move( unsigned int _playerIndex, PlayerTransform _transform, PlayerAnimation _animation )
	{
		index = 101;
		playerIndex = _playerIndex;
		transform = _transform;
		animation = _animation;
	}

	::std::wstring GetName(){ return L"N_Move"; }
	static unsigned int GetIndex(){ return 101; }
};

inline StreamReader& operator>>( StreamReader& stream, N_Move& val )
{
	return stream>>val.playerIndex>>val.transform>>val.animation;
}

inline StreamWriter& operator<<( StreamWriter& stream, N_Move& val )
{
	return stream<<val.playerIndex<<val.transform<<val.animation;
}

struct N_Roll : public ::Noob::Packet
{
	unsigned int playerIndex;
	float degree;

	N_Roll()
	{
		index = 102;
	}

	N_Roll( unsigned int _playerIndex, float _degree )
	{
		index = 102;
		playerIndex = _playerIndex;
		degree = _degree;
	}

	::std::wstring GetName(){ return L"N_Roll"; }
	static unsigned int GetIndex(){ return 102; }
};

inline StreamReader& operator>>( StreamReader& stream, N_Roll& val )
{
	return stream>>val.playerIndex>>val.degree;
}

inline StreamWriter& operator<<( StreamWriter& stream, N_Roll& val )
{
	return stream<<val.playerIndex<<val.degree;
}

struct N_Chat : public ::Noob::Packet
{
	unsigned int playerIndex;
	::std::wstring message;

	N_Chat()
	{
		index = 103;
	}

	N_Chat( unsigned int _playerIndex, ::std::wstring _message )
	{
		index = 103;
		playerIndex = _playerIndex;
		message = _message;
	}

	::std::wstring GetName(){ return L"N_Chat"; }
	static unsigned int GetIndex(){ return 103; }
};

inline StreamReader& operator>>( StreamReader& stream, N_Chat& val )
{
	return stream>>val.playerIndex>>val.message;
}

inline StreamWriter& operator<<( StreamWriter& stream, N_Chat& val )
{
	return stream<<val.playerIndex<<val.message;
}

#pragma once

#include "../Datas/Math.h"
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

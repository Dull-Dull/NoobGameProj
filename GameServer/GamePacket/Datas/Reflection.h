#pragma once


enum class PLAYER_STATE : unsigned int
{
	STOP,
	RUN,
	DEAD,
	__MAX__
};

inline StreamReader& operator>>( StreamReader& stream, PLAYER_STATE& val )
{
	return stream >> *reinterpret_cast<unsigned int*>(&val);
}
inline StreamWriter& operator<<( StreamWriter& stream, PLAYER_STATE& val )
{
	return stream << static_cast<unsigned int>(val);
}

struct PlayerTransform
{
	::Noob::Vector2D position;
	::Noob::Vector2D velocity;

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

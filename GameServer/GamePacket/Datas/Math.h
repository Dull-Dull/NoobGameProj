#pragma once


struct Vector2D
{
	float x;
	float y;

	static std::wstring GetName(){ return L"Vector2D"; }
};

inline StreamReader& operator>>( StreamReader& stream, Vector2D& val )
{
	return stream>>val.x>>val.y;
}

inline StreamWriter& operator<<( StreamWriter& stream, Vector2D& val )
{
	return stream<<val.x<<val.y;
}

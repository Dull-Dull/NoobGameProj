#pragma once


struct Vector2D
{
	float X;
	float Y;

	static std::wstring GetName(){ return L"Vector2D"; }
};

inline StreamReader& operator>>( StreamReader& stream, Vector2D& val )
{
	return stream>>val.X>>val.Y;
}

inline StreamWriter& operator<<( StreamWriter& stream, Vector2D& val )
{
	return stream<<val.X<<val.Y;
}

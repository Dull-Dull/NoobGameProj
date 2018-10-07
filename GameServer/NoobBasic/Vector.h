#pragma once

namespace Noob{

class Vector2D
{
public:
	float x;
	float y;

	Vector2D() : x( 0.0f ), y( 0.0f ){}
	Vector2D( float _x, float _y ) : x( _x ), y( _y ){}
	Vector2D( const Vector2D& rhs ) : x( rhs.x ), y( rhs.y ){}

	Vector2D& operator = ( const Vector2D& rhs );
	bool operator == ( const Vector2D& rhs ) const;
	bool operator != ( const Vector2D& rhs ) const;

	Vector2D& operator += ( const Vector2D& rhs );
	Vector2D& operator -= ( const Vector2D& rhs );
	Vector2D& operator *= ( float scalar );
	Vector2D& operator /= ( float scalar );
	Vector2D operator + ( const Vector2D& rhs );
	Vector2D operator - ( const Vector2D& rhs );
	Vector2D operator * ( float scalar ) const;
	Vector2D operator / ( float scalar ) const;

	float Length() const;
	Vector2D Normalize() const;

	static float Dot( const Vector2D& val1, const Vector2D& val2 );
};

}

::Noob::Vector2D operator * ( float lhs, const ::Noob::Vector2D& rhs );

struct StreamReader;
struct StreamWriter;

StreamReader& operator>>( StreamReader& stream, ::Noob::Vector2D& val );
StreamWriter& operator<<( StreamWriter& stream, ::Noob::Vector2D& val );
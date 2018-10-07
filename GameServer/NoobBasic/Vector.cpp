#include "PreCompiled.h"
#include "Vector.h"

#include "Serialize.hpp"
#include <algorithm>
#include <cmath>

namespace Noob{

Vector2D& Vector2D::operator = ( const Vector2D& rhs )
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

bool Vector2D::operator == ( const Vector2D& rhs ) const
{
	float epsilon = ::std::numeric_limits<float>::epsilon();
	if( ::std::abs( x - rhs.x ) < epsilon &&
		::std::abs( y - rhs.y ) < epsilon )
		return true;
	else
		return false;
}

bool Vector2D::operator != ( const Vector2D& rhs ) const
{
	float epsilon = ::std::numeric_limits<float>::epsilon();
	if( ::std::abs( x - rhs.x ) >= epsilon ||
		::std::abs( y - rhs.y ) >= epsilon )
		return true;
	else
		return false;
}

Vector2D& Vector2D::operator += ( const Vector2D& rhs )
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2D& Vector2D::operator -= ( const Vector2D& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2D& Vector2D::operator *= ( float scalar )
{
	x *= scalar;
	y *= scalar;
	return *this;
}
Vector2D& Vector2D::operator /= ( float scalar )
{
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2D Vector2D::operator + ( const Vector2D& rhs )
{
	Vector2D temp( x + rhs.x, y + rhs.y );
	return temp;
}

Vector2D Vector2D::operator - ( const Vector2D& rhs )
{
	Vector2D temp( x - rhs.x, y - rhs.y );
	return temp;
}

Vector2D Vector2D::operator * ( float scalar ) const
{
	Vector2D temp( x * scalar, y * scalar );
	return temp;
}

Vector2D Vector2D::operator / ( float scalar ) const
{
	Vector2D temp( x / scalar, y / scalar );
	return temp;
}

float Vector2D::Length() const
{
	return ::std::sqrtf( (x*x) + (y*y) );
}

Vector2D Vector2D::Normalize() const
{
	float len = Length();
	return Vector2D( x/len, y/len );
}

float Vector2D::Dot( const Vector2D& val1, const Vector2D& val2 )
{
	return ( val1.x * val2.x ) + ( val1.y * val2.y );
}

}

::Noob::Vector2D operator * ( float lhs, const ::Noob::Vector2D& rhs )
{
	return ::Noob::Vector2D( rhs.x * lhs, rhs.y * lhs );
}

StreamReader& operator >> ( StreamReader& stream, ::Noob::Vector2D& val )
{
	return stream >> val.x >> val.y;
}

StreamWriter& operator<<( StreamWriter& stream, ::Noob::Vector2D& val )
{
	return stream << val.x << val.y;
}
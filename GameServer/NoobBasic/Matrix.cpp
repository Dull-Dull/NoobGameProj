#include "PreCompiled.h"
#include "Matrix.h"

namespace Noob
{

Matrix33::Matrix33()
{
	memset( val, 0, sizeof( float ) * 3 * 3 );
}

Matrix33::Matrix33( const Matrix33& matrix )
{
	memcpy( val, matrix.val, sizeof( float ) * 3 * 3 );
}

Matrix33& Matrix33::operator = ( const Matrix33& rhs )
{
	memcpy( val, rhs.val, sizeof( float ) * 3 * 3 );
	return *this;
}

Matrix33 Matrix33::operator + ( const Matrix33& rhs ) const
{
	Matrix33 temp;
	
	temp.val[0][0] = val[0][0] + rhs.val[0][0];
	temp.val[0][1] = val[0][1] + rhs.val[0][1];
	temp.val[0][2] = val[0][2] + rhs.val[0][2];
	temp.val[1][0] = val[1][0] + rhs.val[1][0];
	temp.val[1][1] = val[1][1] + rhs.val[1][1];
	temp.val[1][2] = val[1][2] + rhs.val[1][2];
	temp.val[2][0] = val[2][0] + rhs.val[2][0];
	temp.val[2][1] = val[2][1] + rhs.val[2][1];
	temp.val[2][2] = val[2][2] + rhs.val[2][2];

	return temp;
}

Matrix33 Matrix33::operator - ( const Matrix33& rhs ) const
{
	Matrix33 temp;

	temp.val[0][0] = val[0][0] - rhs.val[0][0];
	temp.val[0][1] = val[0][1] - rhs.val[0][1];
	temp.val[0][2] = val[0][2] - rhs.val[0][2];
	temp.val[1][0] = val[1][0] - rhs.val[1][0];
	temp.val[1][1] = val[1][1] - rhs.val[1][1];
	temp.val[1][2] = val[1][2] - rhs.val[1][2];
	temp.val[2][0] = val[2][0] - rhs.val[2][0];
	temp.val[2][1] = val[2][1] - rhs.val[2][1];
	temp.val[2][2] = val[2][2] - rhs.val[2][2];

	return temp;
}

Matrix33 Matrix33::operator * ( const Matrix33& rhs ) const
{
	Matrix33 temp;

	temp.val[0][0] = val[0][0] * rhs.val[0][0] + val[0][1] * rhs.val[1][0] + val[0][2] * rhs.val[2][0];
	temp.val[0][1] = val[0][0] * rhs.val[0][1] + val[0][1] * rhs.val[1][1] + val[0][2] * rhs.val[2][1];
	temp.val[0][2] = val[0][0] * rhs.val[0][2] + val[0][1] * rhs.val[1][2] + val[0][2] * rhs.val[2][2];
	temp.val[1][0] = val[1][0] * rhs.val[0][0] + val[1][1] * rhs.val[1][0] + val[1][2] * rhs.val[2][0];
	temp.val[1][1] = val[1][0] * rhs.val[0][1] + val[1][1] * rhs.val[1][1] + val[1][2] * rhs.val[2][1];
	temp.val[1][2] = val[1][0] * rhs.val[0][2] + val[1][1] * rhs.val[1][2] + val[1][2] * rhs.val[2][2];
	temp.val[2][0] = val[2][0] * rhs.val[0][0] + val[2][1] * rhs.val[1][0] + val[2][2] * rhs.val[2][0];
	temp.val[2][1] = val[2][0] * rhs.val[0][1] + val[2][1] * rhs.val[1][1] + val[2][2] * rhs.val[2][1];
	temp.val[2][2] = val[2][0] * rhs.val[0][2] + val[2][1] * rhs.val[1][2] + val[2][2] * rhs.val[2][2];

	return temp;
}

Matrix33 Matrix33::operator * ( float rhs ) const
{
	Matrix33 temp;

	temp.val[0][0] = val[0][0] * rhs;
	temp.val[0][1] = val[0][1] * rhs;
	temp.val[0][2] = val[0][2] * rhs;
	temp.val[1][0] = val[1][0] * rhs;
	temp.val[1][1] = val[1][1] * rhs;
	temp.val[1][2] = val[1][2] * rhs;
	temp.val[2][0] = val[2][0] * rhs;
	temp.val[2][1] = val[2][1] * rhs;
	temp.val[2][2] = val[2][2] * rhs;

	return temp;
}

Matrix33 Matrix33::operator / ( float rhs ) const
{
	Matrix33 temp;

	temp.val[0][0] = val[0][0] / rhs;
	temp.val[0][1] = val[0][1] / rhs;
	temp.val[0][2] = val[0][2] / rhs;
	temp.val[1][0] = val[1][0] / rhs;
	temp.val[1][1] = val[1][1] / rhs;
	temp.val[1][2] = val[1][2] / rhs;
	temp.val[2][0] = val[2][0] / rhs;
	temp.val[2][1] = val[2][1] / rhs;
	temp.val[2][2] = val[2][2] / rhs;

	return temp;
}

Matrix33 Matrix33::GetPower() const
{
	return (*this) * (*this);
}

Matrix33 Matrix33::GetInverse() const
{
	float det = val[0][0] * ( 1.0f / ( (val[1][1]*val[2][2]) - (val[1][2]*val[2][1]) ) )
		- val[0][1] * ( 1.0f / ( (val[1][0]*val[2][2]) - (val[1][2]*val[2][0]) ) )
		+ val[0][2] * ( 1.0f / ( (val[1][0]*val[2][1]) - (val[1][1]*val[2][0] ) ) );

	return det * (*this);
}

Matrix33 Matrix33::GetTranspose() const
{
	Matrix33 temp;

	temp.val[0][0] = val[0][0];
	temp.val[0][1] = val[1][0];
	temp.val[0][2] = val[2][0];
	temp.val[1][0] = val[0][1];
	temp.val[1][1] = val[2][1];
	temp.val[1][2] = val[2][1];
	temp.val[2][0] = val[0][2];
	temp.val[2][1] = val[1][2];
	temp.val[2][2] = val[2][2];

	return temp;
}

Matrix33 Matrix33::GetIdentity()
{
	Matrix33 temp;

	temp.val[0][0] = 1.0f;
	temp.val[1][1] = 1.0f;
	temp.val[2][2] = 1.0f;

	return temp;
}

Matrix33 Matrix33::GetTransform( const Vector2D& val )
{
	Matrix33 temp = Matrix33::GetIdentity();

	temp.val[2][0] = val.x;
	temp.val[2][1] = val.y;

	return temp;
}

Matrix33 Matrix33::GetRotate( const Vector2D& val )
{
	Matrix33 temp;
	float dot = Vector2D::Dot( val, Vector2D( 1.0f, 0.0f) );

	temp.val[0][0] = dot;
	temp.val[0][1] = 1.0f/dot;
	temp.val[1][0] = -(1.0f/dot);
	temp.val[1][1] = dot;
	temp.val[2][2] = 1.0f;

	return temp;
}

Matrix33 Matrix33::GetRotate( float degree )
{
	Matrix33 temp;
	float cos_t = ::std::cosf( degree );
	float sin_t = 1.0f/cos_t;

	temp.val[0][0] = cos_t;
	temp.val[0][1] = sin_t;
	temp.val[1][0] = -sin_t;
	temp.val[1][1] = cos_t;
	temp.val[2][2] = 1.0f;

	return temp;
}

Matrix33 Matrix33::GetScale( const Vector2D& val )
{
	Matrix33 temp;

	temp.val[0][0] = val.x;
	temp.val[1][1] = val.y;
	temp.val[2][2] = 0.0f;

	return temp;
}

}

::Noob::Vector2D operator * ( const ::Noob::Vector2D& lhs, const ::Noob::Matrix33& rhs )
{
	::Noob::Vector2D temp;

	temp.x = lhs.x * rhs.val[0][0] + lhs.y * rhs.val[1][0] + rhs.val[2][0];
	temp.y = lhs.x * rhs.val[0][1] + lhs.y * rhs.val[1][1] + rhs.val[2][1];

	return temp;
}

::Noob::Matrix33 operator * ( float lhs, const ::Noob::Matrix33& rhs )
{
	::Noob::Matrix33 temp;

	temp.val[0][0] = rhs.val[0][0] * lhs;
	temp.val[0][1] = rhs.val[0][1] * lhs;
	temp.val[0][2] = rhs.val[0][2] * lhs;
	temp.val[1][0] = rhs.val[1][0] * lhs;
	temp.val[1][2] = rhs.val[1][2] * lhs;
	temp.val[1][3] = rhs.val[1][3] * lhs;
	temp.val[2][0] = rhs.val[2][0] * lhs;
	temp.val[2][1] = rhs.val[2][1] * lhs;
	temp.val[2][2] = rhs.val[2][2] * lhs;

	return temp;
}
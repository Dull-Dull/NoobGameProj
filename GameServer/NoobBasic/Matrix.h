#pragma once
#include "Vector.h"

namespace Noob {

class Matrix33
{
public:
	float val[3][3];

	Matrix33();
	Matrix33( const Matrix33& matrix );

	Matrix33& operator = ( const Matrix33& rhs );

	Matrix33 operator + ( const Matrix33& rhs ) const;
	Matrix33 operator - ( const Matrix33& rhs ) const;
	Matrix33 operator * ( const Matrix33& rhs ) const;
	Matrix33 operator * ( float rhs ) const;
	Matrix33 operator / ( float rhs ) const;

	Matrix33 GetPower() const;
	Matrix33 GetInverse() const;
	Matrix33 GetTranspose() const;

	static Matrix33 GetIdentity();
	static Matrix33 GetTransform( const Vector2D& val );
	static Matrix33 GetRotate( const Vector2D& val );
	static Matrix33 GetRotate( float degree );
	static Matrix33 GetScale( const Vector2D& val );
};

}

::Noob::Vector2D operator * ( const ::Noob::Vector2D& lhs, const ::Noob::Matrix33& rhs );
::Noob::Matrix33 operator * ( float lhs, const ::Noob::Matrix33& rhs );
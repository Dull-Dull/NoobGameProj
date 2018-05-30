#pragma once

#include "RefCnt.h"

namespace Noob
{

template<typename Type>
class Ptr
{
public:
	using element_type = Type;

public:
	Ptr()
	{
		obj = nullptr;
	}

	Ptr( Type* ptr )
	{
		obj = ptr;

		if( obj != nullptr )			
			obj->IncCnt();
	}

	Ptr( const Ptr<Type>& ptr )
	{
		obj = (ptr.obj);
		obj->IncCnt();
	}

	virtual ~Ptr()
	{
		decAndCheckObj();
	}

	Ptr<Type>& operator = ( const Ptr<Type>& ptr )
	{
		decAndCheckObj();

		obj = ptr.obj;
		if( obj != nullptr )
			obj->IncCnt();

		return *this;
	}

	Ptr<Type>& operator = ( Type* ptr )
	{
		decAndCheckObj();

		obj = ptr;
		if( obj != nullptr )
			obj->IncCnt();

		return *this;
	}

	bool operator == ( const Ptr<Type>& rhs ) const
	{
		return obj == rhs.obj;
	}

	Type& operator * () const
	{
		return *obj;
	}

	Type* operator -> () const
	{
		return obj;
	}

	Type* Get() const
	{
		return obj;
	}

private:
	void decAndCheckObj()
	{
		if( obj != nullptr )
		{
			obj->DecCnt();

			if( obj->GetRefCnt() == 0 )
				delete obj;
		}
	}

	Type* obj;
};

using RefCntPtr = Ptr<RefCnt>;

template< class TargetType, class SrcType >
Ptr<TargetType> PtrCast( const Ptr<SrcType>& src )
{
	TargetType* target = reinterpret_cast<TargetType*>( src.Get() );
	return Ptr<TargetType>( target );
}

#define DECL( TYPE ) class TYPE;\
using TYPE##Ptr = ::Noob::Ptr<TYPE>;

}

namespace std {

template< class Type >
struct hash< ::Noob::Ptr<Type> >
{
	size_t operator()( const ::Noob::Ptr<Type>& ptr ) const
	{
		return reinterpret_cast< size_t >( ptr.Get() );
	}
};

}
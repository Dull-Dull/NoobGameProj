#pragma once

#include "RefCnt.h"

namespace Noob
{

template<typename Type>
class Ptr
{
public:
	Ptr()
	{
		obj = nullptr;
	}

	Ptr( Type* ptr )
	{
		obj = ptr;

		if( ptr!=nullptr )			
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

		obj->IncCnt();

		return *this;
	}

	Ptr<Type>& operator = ( Type* ptr )
	{
		decAndCheckObj();

		obj = ptr;
		obj->IncCnt();

		return *this;
	}

	Type& operator * ()
	{
		return *obj;
	}

	Type* operator -> ()
	{
		return obj;
	}

	Type* Get()
	{
		return obj;
	}

private:
	void decAndCheckObj()
	{
		if( obj!=nullptr )
		{
			obj->DecCnt();

			if( obj->GetRefCnt() == 0 )
				delete obj;
		}
	}

	Type* obj;
};

using RefCntPtr = Ptr<RefCnt>;

}
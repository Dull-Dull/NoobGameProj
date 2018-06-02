#pragma once

namespace Noob
{

template< class Type >
class Singletone
{
public:
	static Type* GetInstance()
	{
		if( instance == nullptr )
			instance = new Type;

		return instance;
	}
protected:
	Singletone(){};
	Singletone( const Singletone& ) = delete;

private:
	static Type* instance;
};

template< class Type >
Type* Singletone<Type>::instance = nullptr;

}
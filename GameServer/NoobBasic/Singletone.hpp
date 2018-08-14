#pragma once

namespace Noob
{

template< class Type >
class Singletone
{
public:
	static Type* GetInstance()
	{
		Type* instance = m_instance.load( ::std::memory_order_acquire );
		if( instance == nullptr )
		{
			LockGuard lockGuard( m_lock );
			instance = m_instance.load( ::std::memory_order_relaxed );
			if( instance == nullptr )
			{
				instance = new Type;
				m_instance.store( instance, ::std::memory_order_release );
			}
		}

		return instance;
	}
protected:
	Singletone(){};
	Singletone( const Singletone& ) = delete;

private:
	static ::std::atomic<Type*> m_instance;
	static Lock m_lock;
};

template< class Type >
::std::atomic<Type*> Singletone<Type>::m_instance;

template< class Type >
Lock Singletone<Type>::m_lock;

}
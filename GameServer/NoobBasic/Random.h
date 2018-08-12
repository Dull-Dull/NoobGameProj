#pragma once

namespace Noob {

class Random
{
public:
	template< class Type >
	static Type GetInteger( Type min, Type max )
	{
		static_assert( ::std::is_integral<Type>::value, "Invalid Type" );
		::std::uniform_int_distribution<Type> distribution( min, max );
		return distribution( m_engine );
	}

	template< class Type >
	static Type GetFloat( Type min, Type max )
	{
		static_assert( ::std::is_floating_point<Type>::value, "Invalid Type" );
		::std::uniform_real_distribution<Type> distribution( min, max );
		return distribution( m_engine );
	}

private:
	thread_local static ::std::default_random_engine m_engine;
};

}
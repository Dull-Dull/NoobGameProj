#pragma once

#include <type_traits>
#include "IUser.h"
#include "PingPacket.h"

DECL_STRUCT( Packet );

namespace Noob
{

template< class UserType >
class PacketDispatcher
{
public:
	static_assert( ::std::is_base_of<IUser, UserType>::value, "Invalid UserType" );
	using Func = void ( UserType::* )( const ::Noob::PacketPtr& );
	using Container = ::std::unordered_map< unsigned int, PacketDispatcher::Func >;

	static void Call( UserType* user, const ::Noob::PacketPtr& pck )
	{
		auto iter = m_pckProcCon->find( pck->index );
		if( iter != m_pckProcCon->end() )
			( user->*( iter->second ) )( pck );
	}
private:
	static Container* m_pckProcCon;
	template<class UserType> friend class PacketProcRegisterer;
};

template< class UserType >
typename PacketDispatcher<UserType>::Container* PacketDispatcher<UserType>::m_pckProcCon = nullptr;


template< class UserType >
class PacketProcRegisterer
{
public:
	PacketProcRegisterer( unsigned int pckIndex, typename PacketDispatcher< UserType >::Func callbackFunc )
	{
		if( PacketDispatcher< UserType >::m_pckProcCon == nullptr )
		{
			PacketDispatcher< UserType >::m_pckProcCon = new PacketDispatcher< UserType >::Container();
			PacketDispatcher< UserType >::m_pckProcCon->emplace( CS_Ping::GetIndex(),
				reinterpret_cast< typename PacketDispatcher< UserType >::Func >( &::Noob::IUser::OnPacket<CS_Ping> ) );
		}			

		if( PacketDispatcher< UserType >::m_pckProcCon->find( pckIndex ) != PacketDispatcher< UserType >::m_pckProcCon->end() )
			assert( false );

		PacketDispatcher< UserType >::m_pckProcCon->emplace( pckIndex, callbackFunc );
	}
};

#define REGISTER_PCK_PROC( USER_TYPE, PACKET_TYPE )\
DECL_STRUCT( PACKET_TYPE );\
template<> void USER_TYPE::OnPacket< PACKET_TYPE >(const ::Noob::Ptr<PACKET_TYPE>&);\
::Noob::PacketProcRegisterer<USER_TYPE> __##PACKET_TYPE##Registerer( PACKET_TYPE::GetIndex(),\
reinterpret_cast<::Noob::PacketDispatcher<USER_TYPE>::Func>( &USER_TYPE::OnPacket<PACKET_TYPE> ) );\
template<>

}
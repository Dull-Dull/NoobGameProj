#pragma once

#include "TcpSession.h"


DECL_STRUCT( Packet );
DECL_STRUCT( CS_Ping );

namespace Noob
{

DECL_CLASS( TcpSession );
class PingManager;
class Dispatcher;

class IUser : public ::Noob::RefCnt
{
public:
	IUser( ::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher );
	virtual ~IUser();

	virtual void OnAccept() {};
	virtual void OnConnect() {};
	virtual void OnRecv( ::Noob::PacketPtr pck ) = 0;
	virtual void OnClose() = 0;

	template< typename PacketType >
	void Send( PacketType& pck )
	{
		if( m_session.Get() != nullptr )
			m_session->Send( pck );
	}

	void Close();

	template< class PacketType >
	void OnPacket( const ::Noob::Ptr<PacketType>& pck ){ static_assert( false, "Invalid Pck" ); }

	template<>
	void IUser::OnPacket( const CS_PingPtr& pck );

	Dispatcher* GetDispatcher(){ return m_dispatcher; }
	TcpSession* GetSession(){ return m_session.Get(); }
	::Noob::Tick GetPing();

private:
	TcpSessionPtr m_session;
	PingManager* m_ping;
	Dispatcher* m_dispatcher;

	friend Dispatcher;
};

using IUserPtr = ::Noob::Ptr<IUser>;

}
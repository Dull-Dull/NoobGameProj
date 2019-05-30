#pragma once

#include "TcpSession.h"
#include "PingPacket.h"

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

	void OnPingPacket( const PingPtr& pck );

	template< typename PacketType >
	void Send( PacketType& pck )
	{
		if( m_session.Get() != nullptr )
			m_session->Send( pck );
	}

	template< typename PacketType >
	void Send( const Ptr<PacketType>& pck )
	{
		if( m_session.Get() != nullptr )
			m_session->Send( *( pck.Get() ) );
	}

	void Close();

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
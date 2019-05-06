#pragma once

namespace Noob
{

DECL_CLASS( TcpSession );
DECL_STRUCT( Packet );
class PingManager;
class TcpSession;
class Dispatcher;

class IUser : public ::Noob::RefCnt
{
public:
	IUser( ::Noob::TcpSessionPtr session, Dispatcher* dispatcher );
	virtual ~IUser();

	virtual void OnAccept() = 0;
	virtual void OnRecv( ::Noob::PacketPtr pck ) = 0;
	virtual void OnClose() = 0;

	template< typename PacketType >
	void Send( PacketType& pck )
	{
		if( m_session != nullptr )
			m_session->Send( pck );
	}

	void Close();

	template< class PacketType >
	void OnPacket( const ::Noob::Ptr<PacketType>& pck ){ static_assert( false, "Invalid Pck" ); }

	Dispatcher* GetDispatcher(){ return m_dispatcher; }
	TcpSession* GetSession(){ return m_session.Get(); }

private:
	void __onAccept();
	void __onClose();

	TcpSessionPtr m_session;
	PingManager* m_ping;
	Dispatcher* m_dispatcher;

	friend Dispatcher;
};

using IUserPtr = ::Noob::Ptr<IUser>;

}
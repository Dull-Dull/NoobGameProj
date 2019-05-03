#pragma once

namespace Noob
{

class PingManager;
class TcpSession;
class Dispatcher;

class IUser : public ::Noob::RefCnt
{
public:
	IUser( ::Noob::TcpSession* session, Dispatcher* dispatcher );
	virtual ~IUser();

	virtual void OnAccept() = 0;
	virtual void OnRecv( ::Noob::PacketPtr pck ) = 0;
	virtual void OnClose() = 0;

	template< typename PacketType >
	void Send( PacketType& pck )
	{
		m_session->Send( pck );
	}

	void Close();

	template< class PacketType >
	void OnPacket( const ::Noob::Ptr<PacketType>& pck ){ static_assert( false, "Invalid Pck" ); }

private:
	void __onAccept();
	void __onClose();

	TcpSession* m_session;
	PingManager* m_ping;
	Dispatcher* m_dispatcher;

	friend Dispatcher;
};

}
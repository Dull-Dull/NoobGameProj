#pragma once

#include "EndPoint.h"
#include "Overlapped.h"
#include "Iocp.h"
#include "Packet.h"

namespace Noob
{

class IAcceptor;
class IConnector;

class ITcpSession : public RefCnt
{
public:
	ITcpSession();
	virtual ~ITcpSession();

	void Init( Iocp* iocp, SOCKET sock, const EndPoint& local, const EndPoint& remote );

	template< typename PacketType >
	void Send( PacketType& pck )
	{
		static_assert( ::std::is_base_of<Packet,PacketType>::value, "Invalid Packet" );

		if( m_sendOverlapped.object.Get() == nullptr )
			return;

		StreamBuf streamBuf;
		StreamWriter writer( streamBuf );
		writer.m_offSet = sizeof( PacketHeader );

		writer << pck;

		PacketHeader* header = reinterpret_cast<PacketHeader*>( streamBuf.m_rowBuf );
		header->index = PacketType::GetIndex();
		header->length = writer.m_offSet;

		WSABUF buff;
		buff.buf = reinterpret_cast<char*>( streamBuf.m_rowBuf );
		buff.len = writer.m_offSet;
		
		{
			LockGuard lockGuard( m_sendLock );

			m_consumeBuff->push_back( buff );
			if( !m_nowSending && m_sendOverlapped.object.Get() != nullptr )
			{
				PostSend();
			}
		}
	}

	void Close();

	const EndPoint& GetLocal(){ return m_localEndPoint; }
	const EndPoint& GetRemote(){ return m_remoteEndPoint; }

protected:
	virtual void OnAccept( IAcceptor* acceptor ){}
	virtual void OnConnect(){}
	virtual void OnRecv( PacketPtr pck ) = 0;
	virtual void OnSend(){}
	virtual void OnClose() = 0;
private:
	void OnRecvForIocp( bool success, unsigned int transferedLen );
	void OnSendForIocp( bool success, unsigned int transferedLen );

	void PostRecv();
	void PostSend();

private:
	Iocp* m_iocp;
	SOCKET m_sock;
	EndPoint m_localEndPoint;
	EndPoint m_remoteEndPoint;

	Overlapped m_recvOverlapped;	
	WSABUF m_recvBuff;
	unsigned long m_recvFlag;
	unsigned int m_recvBuffSize;
	unsigned int m_recvBuffOffSet;
	unsigned int m_recvLen;


	Overlapped m_sendOverlapped;
	using WsaBuffContainer = ::std::vector<WSABUF>;
	WsaBuffContainer* m_consumeBuff;
	WsaBuffContainer* m_sendingBuff;
	bool m_nowSending;
	unsigned int m_sendLen;
	Lock m_sendLock;

	friend IAcceptor;
	friend IConnector;
	friend Iocp;
};

}

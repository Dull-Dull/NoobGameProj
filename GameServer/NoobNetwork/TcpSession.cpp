#include "PreCompiled.h"
#include "TcpSession.h"
#include "PacketFactory.h"

namespace Noob
{

const static unsigned int gNetBuffSize = 4096;

ITcpSession::ITcpSession() : m_recvOverlapped( Overlapped::IO_TYPE::RECV, this),
							m_sendOverlapped( Overlapped::IO_TYPE::SEND, this ),
							m_recvBuffSize( gNetBuffSize ), m_recvBuffOffSet(0),
							m_recvLen( 0 ), m_recvFlag( 0 ),
							m_consumeBuff( new WsaBuffContainer ), m_sendingBuff( new WsaBuffContainer ),
							m_nowSending(false )
{
	m_recvBuff.len = 0;
	m_recvBuff.buf = new char[ m_recvBuffSize ];
}

ITcpSession::~ITcpSession()
{
	for( auto& buff : *m_consumeBuff )
		delete[] buff.buf;

	for( auto& buff : *m_sendingBuff )
		delete[] buff.buf;

	delete m_consumeBuff;
	delete m_sendingBuff;
	delete [] m_recvBuff.buf;
}

void ITcpSession::Init( Iocp* iocp, SOCKET sock, const EndPoint& local, const EndPoint& remote )
{
	m_iocp = iocp;
	m_sock = sock;
	m_localEndPoint = local;
	m_remoteEndPoint = remote;
	m_iocp->Regist( m_sock );
}

void ITcpSession::PostSend()
{
	WsaBuffContainer* temp = m_consumeBuff;
	m_consumeBuff = m_sendingBuff;
	m_sendingBuff = temp;

	if( WSASend( m_sock, &( *m_sendingBuff )[0], static_cast<DWORD>( m_sendingBuff->size() ),
		reinterpret_cast<DWORD*>( &m_sendLen ), 0, &m_sendOverlapped, NULL ) == SOCKET_ERROR )
	{
		int err = WSAGetLastError();
		if( err != WSA_IO_PENDING )
		{
			Log( LOG_TYPE::ERROR, L"WSASendError", err );
		}
	}

	m_nowSending = true;
}

void ITcpSession::OnSendForIocp( bool success, unsigned int transferedLen )
{
	for( const auto& wsaBuf : *m_sendingBuff )
		delete[] wsaBuf.buf;
	m_sendingBuff->clear();

	if( success == false || transferedLen == 0 )
	{
		m_sendOverlapped.object = nullptr;
		return;
	}
	else
	{
		LockGuard lockGuard( m_sendLock );
		m_nowSending = false;

		if( m_consumeBuff->empty() )
			return;

		PostSend();
	}
}

void ITcpSession::Close()
{
	shutdown( m_sock, SD_BOTH );
	closesocket( m_sock );
	m_sock = NULL;
}

void ITcpSession::OnRecvForIocp( bool success, unsigned int transferedLen )
{
	if( success == false || transferedLen == 0 )
	{
		{
			LockGuard lock( m_sendLock );
			if( false == m_nowSending )
				m_sendOverlapped.object = nullptr;
		}

		OnClose();
		m_recvOverlapped.object = nullptr;

		return;
	}

	m_recvBuffOffSet += transferedLen;

	while( true )
	{
		if( m_recvBuffOffSet < sizeof( PacketHeader ) )
		{
			PostRecv();
			return;
		}

		PacketHeader* header = reinterpret_cast<PacketHeader*>( m_recvBuff.buf );
		unsigned int totalPckLen = header->length;

		if( m_recvBuffSize < totalPckLen )
		{
			char* tempBuff = new char[ totalPckLen ];
			memcpy( tempBuff, m_recvBuff.buf, m_recvBuffOffSet );
			delete [] m_recvBuff.buf;
			m_recvBuff.buf = tempBuff;
			m_recvBuffSize = header->length;
			Log( LOG_TYPE::WARNING, L"PckRecvBuff Realloc", header->length );

			PostRecv();
			return;
		}

		if( m_recvBuffOffSet < totalPckLen )
		{
			PostRecv();
			return;
		}

		Packet* pck = PacketFactory::CreatePacket( header, m_recvBuff.buf + sizeof( PacketHeader ) );
		OnRecv( pck );
		
		m_recvBuffOffSet -= totalPckLen;
		memmove( m_recvBuff.buf, m_recvBuff.buf + totalPckLen, m_recvBuffOffSet );
	}
}

void ITcpSession::PostRecv()
{
	m_recvBuff.len = m_recvBuffSize - m_recvBuffOffSet;

	if( SOCKET_ERROR == WSARecv( m_sock, &m_recvBuff, 1, (DWORD*)&m_recvLen, &m_recvFlag, &m_recvOverlapped, NULL ) )
	{
		int error = WSAGetLastError();
		if( error != WSA_IO_PENDING )
		{
			Log( LOG_TYPE::ERROR, L"WSARecvError", error );
		}
	}
}

}
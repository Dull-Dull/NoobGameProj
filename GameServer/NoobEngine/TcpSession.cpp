#include "PreCompiled.h"
#include "TcpSession.h"

#include "IUser.h"
#include "Dispatcher.h"
#include <concurrent_queue.h>

namespace Noob
{

struct TcpSession::imple
{
	IUserPtr m_user;
	::concurrency::concurrent_queue<::Noob::PacketPtr> m_pckQueue;
};

TcpSession::TcpSession() : pImple( new imple )
{
}

TcpSession::~TcpSession()
{
}

void TcpSession::OnAccept( IUser* user )
{
	pImple->m_user = user;
	pImple->m_user->GetDispatcher()->Push( ::Noob::E_TASK_TYPE::ACCEPT, pImple->m_user.Get() );
}

void TcpSession::OnConnect( IUser* user )
{
	pImple->m_user = user;
	pImple->m_user->GetDispatcher()->Push( ::Noob::E_TASK_TYPE::CONNECT, pImple->m_user.Get() );
}

void TcpSession::OnRecv( ::Noob::PacketPtr pck )
{
	pImple->m_pckQueue.push( pck );
	pImple->m_user->GetDispatcher()->Push( ::Noob::E_TASK_TYPE::RECV, pImple->m_user.Get() );
}

void TcpSession::OnClose()
{
	pImple->m_user->GetDispatcher()->Push( ::Noob::E_TASK_TYPE::CLOSE, pImple->m_user.Get() );
	pImple->m_user = nullptr;
}

::Noob::PacketPtr TcpSession::PopPck()
{
	::Noob::PacketPtr pck = nullptr;
	pImple->m_pckQueue.try_pop( pck );
	return pck;
}

}
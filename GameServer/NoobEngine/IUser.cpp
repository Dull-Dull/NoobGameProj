#include "PreCompiled.h"
#include "IUser.h"

#include "TcpSession.h"
#include "PingManager.h"
#include "PingPacket.h"
#include "Dispatcher.h"

namespace Noob
{

IUser::IUser( ::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher )
	: m_session( session ), m_dispatcher( dispatcher ), m_ping( nullptr ){}

IUser::~IUser()
{
	if( m_session.Get() != nullptr )
	{
		m_session->Close();
		m_session = nullptr;
	}
}

void IUser::OnPingPacket( const PingPtr& pck )
{
	if( m_ping != nullptr )
		m_ping->RecvPing();
	else
		Send( pck );
}

void IUser::Close()
{
	if( m_session.Get() != nullptr )
	{
		m_session->Close();
	}
}

::Noob::Tick IUser::GetPing()
{
	return m_ping->GetPing();
}

}
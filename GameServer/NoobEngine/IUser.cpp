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
	m_session->Close();
	m_session = nullptr;
}

void IUser::OnPingPacket( const CS_PingPtr& pck )
{
	m_ping->RecvPing( pck->tick );
}

void IUser::Close()
{
	m_session->Close();
}

::Noob::Tick IUser::GetPing()
{
	return m_ping->GetPing();
}

}
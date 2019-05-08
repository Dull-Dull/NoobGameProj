#include "PreCompiled.h"
#include "IUser.h"

#include "TcpSession.h"
#include "PingManager.h"
#include "Dispatcher.h"

namespace Noob
{

IUser::IUser( ::Noob::TcpSessionPtr session, Dispatcher* dispatcher )
	: m_session( session ), m_dispatcher( dispatcher ), m_ping( nullptr ){}

IUser::~IUser()
{
	m_session->Close();
	m_session = nullptr;
}

void IUser::Close()
{
	m_session->Close();
}

void IUser::__onAccept()
{
	m_ping = new PingManager( this );
}

void IUser::__onClose()
{
	SAFE_DELETE( m_ping );
}

}
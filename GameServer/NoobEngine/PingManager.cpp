#include "PreCompiled.h"
#include "PingManager.h"

#include "IUser.h"
#include "Dispatcher.h"
#include "AlarmManager.h"
#include "PingPacket.h"

#include <NoobNetwork/PacketRegister.h>

namespace Noob
{

const static int g_maxTryCnt = 3;

PingManager::PingManager( IUser* user )
{
	m_user = user;
	m_pingAlarmIndex = -1;
	m_tryCnt = 0;
	m_bRecvedPing = false;
	m_ping = 0;

	sendPing();
}

PingManager::~PingManager()
{
	if( m_pingAlarmIndex != -1 )
		m_user->GetDispatcher()->GetAlarmManager().UnRegisterAlarm( m_pingAlarmIndex );
}

void PingManager::sendPing()
{
	Ping ping;
	m_user->Send( ping );
	m_sendTime = GetNow();

	m_pingAlarmIndex = m_user->GetDispatcher()->GetAlarmManager().RegisterAlarm( ::Noob::Duration( ::Noob::Second * 1 ), [this](){
		if( m_bRecvedPing )
		{
			m_tryCnt = 0;
			m_bRecvedPing = false;
		}
		else
		{
			m_tryCnt += 1;
#ifndef _DEBUG
			if( m_tryCnt >= g_maxTryCnt )
			{
				m_user->Close();
				return;
			}
#endif
		}
		sendPing();
	} );
}

void PingManager::RecvPing()
{
	if( m_bRecvedPing )
	{
		Log( LOG_TYPE::WARNING, L"Invalid Ping Pck Recv" );
		return;
	}

	m_ping = ( ::Noob::GetNow() - m_sendTime ).count();
	m_bRecvedPing = true;
}

}

REGISTER_PACKET( Ping );
#include "PreCompiled.h"
#include "PingManager.h"

#include "IUser.h"
#include "Dispatcher.h"
#include "AlarmManager.h"
#include "PingPacket.h"

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
}

PingManager::~PingManager()
{
	if( m_pingAlarmIndex != -1 )
		m_user->GetDispatcher()->GetAlarmManager().UnRegisterAlarm( m_pingAlarmIndex );
}

void PingManager::SendPing()
{
	SC_Ping ping;
	ping.tick = ::Noob::GetTick();
	m_user->Send( ping );

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
				m_player->Close();
				return;
			}
#endif
		}
		SendPing();
	} );
}

void PingManager::RecvPing( ::Noob::Tick tick )
{
	m_ping = ::Noob::GetTick() - tick;
	m_bRecvedPing = true;
}

}
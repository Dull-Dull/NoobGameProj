#include "PreCompiled.h"
#include "PingManager.h"

#include "../Player.h"
#include "../../Alarm/AlarmManager.h"

#include <GamePacket/Packets/Login.h>

const static int g_maxTryCnt = 3;

PingManager::PingManager( Player* player )
{
	m_player = player;
	m_pingAlarmIndex = -1;
	m_tryCnt = 0;
	m_bRecvedPing = false;
	m_ping = 0;
}

PingManager::~PingManager()
{
	if( m_pingAlarmIndex != -1 )
	{
		AlarmManager::GetInstance()->UnRegisterAlarm( m_pingAlarmIndex );
	}
}

void PingManager::SendPing()
{
#ifndef _DEBUG
	SC_Ping ping;
	ping.tick = ::Noob::GetTick();
	m_player->Send( ping );

	m_pingAlarmIndex = AlarmManager::GetInstance()->RegisterAlarm( ::Noob::Duration(::Noob::Second * 7), [ this ](){
		if( m_bRecvedPing )
		{
			m_tryCnt = 0;
			m_bRecvedPing = false;
		}
		else
		{
			m_tryCnt += 1;
			if( m_tryCnt >= g_maxTryCnt )
			{
				m_player->Close();
				return;
			}
		}
		SendPing();
	} );
#endif
}

void PingManager::RecvPing( ::Noob::Tick tick )
{
	m_ping = ::Noob::GetTick() - tick;
	m_bRecvedPing = true;
}
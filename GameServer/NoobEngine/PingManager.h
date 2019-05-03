#pragma once

class Player;

class PingManager
{
public:
	PingManager( Player* player );
	~PingManager();

	void SendPing();
	void RecvPing( ::Noob::Tick tick );
	::Noob::Tick GetPing() const{ return m_ping; }
private:
	Player* m_player;
	int64_t m_pingAlarmIndex;
	int m_tryCnt;
	bool m_bRecvedPing;

	::Noob::Tick m_ping;
};
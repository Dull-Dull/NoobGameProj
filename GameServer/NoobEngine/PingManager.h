#pragma once

namespace Noob
{

class IUser;

class PingManager
{
public:
	PingManager( IUser* user );
	~PingManager();

	void RecvPing( ::Noob::Tick tick );
	::Noob::Tick GetPing() const{ return m_ping; }

private:
	IUser* m_user;
	int64_t m_pingAlarmIndex;
	int m_tryCnt;
	bool m_bRecvedPing;

	::Noob::Tick m_ping;

	void sendPing();
};

}
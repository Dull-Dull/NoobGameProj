#pragma once

#include <NoobNetwork\Packet.h>

struct SC_Ping : public ::Noob::Packet
{
	int64_t tick;

	SC_Ping()
	{
		index = 0;
	}

	SC_Ping( int64_t _tick )
	{
		index = 0;
		tick = _tick;
	}

	::std::wstring GetName(){ return L"SC_Ping"; }
	static unsigned int GetIndex(){ return 0; }
};

inline StreamReader& operator>>( StreamReader& stream, SC_Ping& val )
{
	return stream>>val.tick;
}

inline StreamWriter& operator<<( StreamWriter& stream, SC_Ping& val )
{
	return stream<<val.tick;
}

struct CS_Ping : public ::Noob::Packet
{
	int64_t tick;

	CS_Ping()
	{
		index = 1;
	}

	CS_Ping( int64_t _tick )
	{
		index = 1;
		tick = _tick;
	}

	::std::wstring GetName(){ return L"CS_Ping"; }
	static unsigned int GetIndex(){ return 1; }
};

inline StreamReader& operator>>( StreamReader& stream, CS_Ping& val )
{
	return stream>>val.tick;
}

inline StreamWriter& operator<<( StreamWriter& stream, CS_Ping& val )
{
	return stream<<val.tick;
}

namespace Noob
{

class IUser;

class PingManager
{
public:
	PingManager( IUser* user );
	~PingManager();

	void SendPing();
	void RecvPing( ::Noob::Tick tick );
	::Noob::Tick GetPing() const{ return m_ping; }
private:
	IUser* m_user;
	int64_t m_pingAlarmIndex;
	int m_tryCnt;
	bool m_bRecvedPing;

	::Noob::Tick m_ping;
};

}
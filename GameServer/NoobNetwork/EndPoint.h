#pragma once

#include <WS2tcpip.h>

namespace Noob
{

struct EndPoint
{
	unsigned long m_ip;
	short m_port;

	EndPoint()
		: m_ip( 0 ), m_port( 0 ) {}

	EndPoint( unsigned long ip, short port )
		: m_ip( ip ), m_port( port ) {}

	EndPoint( ::std::wstring ip, short port )
		: m_ip( 0 ), m_port( port )
	{
		in_addr addr;
		InetPtonW( AF_INET, ip.c_str(), &addr );
		m_ip = ntohl( addr.s_addr );
	}

	::std::wstring GetIpStr() const
	{
		in_addr addr;
		addr.s_addr = m_ip;

		const size_t buffSize = 17;
		wchar buff[buffSize] = {};

		InetNtopW( AF_INET, &addr, buff, buffSize );

		return buff;
	}
};

}

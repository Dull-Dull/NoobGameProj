#pragma once

namespace Noob {

class WinSockInitor
{
public:
	WinSockInitor()
	{
		WSADATA wsadata = {};
		WSAStartup( MAKEWORD( 2, 2 ), &wsadata );
	}

	~WinSockInitor()
	{
		WSACleanup();
	}

	WinSockInitor(const WinSockInitor&) = delete;
};

}
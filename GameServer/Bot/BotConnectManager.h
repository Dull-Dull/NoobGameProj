#pragma once

class BotConnectManager
{
public:
	static void Connect( ::Noob::Iocp* iocp, ::Noob::EndPoint endPoint, size_t botCnt );
};
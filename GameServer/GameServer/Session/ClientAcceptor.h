#pragma once

class ClientSession;

const static size_t g_AcceptorCnt = 10;
using ClientAcceptor = ::Noob::Acceptor< ClientSession >;
using ClientAcceptorPtr = ::Noob::Ptr< ClientAcceptor >;

class ClientAcceptorManager
{
public:
	ClientAcceptorManager( ::Noob::Iocp* iocp, short port );
	~ClientAcceptorManager();

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};
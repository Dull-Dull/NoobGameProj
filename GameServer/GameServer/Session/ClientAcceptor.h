#pragma once

class GameDispatcher;
class ClientSession;

const static size_t g_AcceptorCnt = 10;

class ClientAcceptor : public ::Noob::Acceptor< ClientSession >
{
public:
	ClientAcceptor( ::Noob::Iocp* iocp, ::Noob::Listener* listener, GameDispatcher* dispatcher );
	GameDispatcher* GetDispatcher();
private:
	GameDispatcher* m_dispatcher;
};
using ClientAcceptorPtr = ::Noob::Ptr<ClientAcceptor>;

class ClientAcceptorManager
{
public:
	ClientAcceptorManager( ::Noob::Iocp* iocp, short port, GameDispatcher* dispatcher );
	~ClientAcceptorManager();

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};
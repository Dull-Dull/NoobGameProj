#pragma once

class Player;
class ClientSession;
class GameDispatcher;

class ClientAcceptor : public ::Noob::Acceptor< ClientSession >
{
public:
	ClientAcceptor( ::Noob::Iocp* iocp, ::Noob::Listener* listener, GameDispatcher* dispatcher );
	GameDispatcher* GetDispatcher();
private:
	GameDispatcher* m_dispatcher;
};

class ClientSession : public ::Noob::ITcpSession, ::Noob::RefCnt
{
public:
	ClientSession();
	virtual ~ClientSession();

	void OnAccept( ::Noob::IAcceptor* acceptor ) override;
	void OnRecv( ::Noob::PacketPtr pck ) override;
	void OnClose();

	void SetPlayer( Player* player );
	Player* GetPlayer();

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};
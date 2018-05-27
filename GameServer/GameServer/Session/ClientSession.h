#pragma once

class Player;

class ClientSession : public ::Noob::ITcpSession
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
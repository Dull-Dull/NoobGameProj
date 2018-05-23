#pragma once

class Player;

class ClientSession : public ::Noob::ITcpSession, ::Noob::RefCnt
{
public:
	ClientSession();
	virtual ~ClientSession();

	void OnAccept( ::Noob::IAcceptor* acceptor ) override;
	void OnRecv( ::Noob::PacketPtr pck ) override;
	void OnClose();

	void SetPlayer( Player* player ){ m_player = player; }
	Player* GetPlayer(){ return m_player; }

private:
	Player* m_player;
};
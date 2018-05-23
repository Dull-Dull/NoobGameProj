#pragma once

class ClientSession;

class Player : public ::Noob::RefCnt
{
	Player();
	~Player();
	
	void OnAccept();
	void OnRecv( ::Noob::PacketPtr pck );
	void OnClose();

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};
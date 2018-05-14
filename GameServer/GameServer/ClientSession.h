#pragma once


class ClientSession : public ::Noob::ITcpSession
{
public:
	ClientSession();
	virtual ~ClientSession();

	void OnAccept( ::Noob::IAcceptor* acceptor ) override;
	void OnRecv( ::Noob::PacketPtr pck ) override;
	void OnClose();

private:
};
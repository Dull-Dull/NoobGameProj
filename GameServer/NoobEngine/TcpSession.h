#pragma once

#include <NoobNetwork/TcpSession.h>

namespace Noob
{

class IPlayer;

class TcpSession : public ::Noob::ITcpSession
{
public:
	TcpSession();
	virtual ~TcpSession();

	void OnAccept( ::Noob::IAcceptor* acceptor ) override;
	void OnRecv( ::Noob::PacketPtr pck ) override;
	void OnClose();

	void SetPlayer( IPlayer* player );

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};

using TcpSessionPtr = ::Noob::Ptr<TcpSession>;

}
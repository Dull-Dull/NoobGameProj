#pragma once

#include <NoobNetwork/TcpSession.h>

namespace Noob
{

DECL_CLASS( IUser );

class TcpSession : public ::Noob::ITcpSession
{
public:
	TcpSession();
	virtual ~TcpSession();

	void OnAccept( IUser* user );
	void OnConnect( IUser* user );
	void OnRecv( ::Noob::PacketPtr pck ) override;
	void OnClose() override;

	::Noob::PacketPtr PopPck();

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};

using TcpSessionPtr = ::Noob::Ptr<TcpSession>;

}
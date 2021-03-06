#pragma once

#include <NoobEngine/IUser.h>

namespace Noob
{
	DECL_CLASS(TcpSession);
	class Dispatcher;
}

class TestServer : public ::Noob::IUser
{
public:
	TestServer(::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher);

	virtual void OnAccept() override;
	virtual void OnRecv(::Noob::PacketPtr pck)  override;
	virtual void OnClose()  override;

	template< class PacketType >
	void OnPacket(const ::Noob::Ptr<PacketType>& pck) { static_assert(false, "Invalid Pck"); }

	static ::std::unordered_set< ::Noob::Ptr<TestServer> >& GetContainer() { return container; }
private:
	static ::std::unordered_set< ::Noob::Ptr<TestServer> > container;
};

DECL_CLASS(TestServer);
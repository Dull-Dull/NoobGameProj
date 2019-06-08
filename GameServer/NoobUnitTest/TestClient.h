#pragma once

#include <NoobEngine/IUser.h>

extern HANDLE g_TestCompleteEvent;

namespace Noob
{
	DECL_CLASS(TcpSession);
	class Dispatcher;
}

class TestClient : public ::Noob::IUser
{
public:
	TestClient( ::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher );

	virtual void OnConnect() override;
	virtual void OnRecv(::Noob::PacketPtr pck)  override;
	virtual void OnClose()  override;

	template< class PacketType >
	void OnPacket(const ::Noob::Ptr<PacketType>& pck) { static_assert(false, "Invalid Pck"); }

	static ::std::unordered_set< ::Noob::Ptr<TestClient> >& GetContainer() { return container; }
private:
	int recvCnt;
	::Noob::TimePoint startTime;

	static ::std::unordered_set< ::Noob::Ptr<TestClient> > container;
};

DECL_CLASS(TestClient);
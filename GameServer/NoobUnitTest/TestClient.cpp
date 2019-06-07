#include "pch.h"
#include "TestClient.h"
#include "CppUnitTest.h"

#include "TestPck/Pck.h"
#include <NoobEngine/PacketDispatcher.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

HANDLE g_TestCompleteEvent = CreateEvent(NULL, true, false, NULL);

TestClient::TestClient(::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher) : IUser( session, dispatcher ){}

void TestClient::OnConnect()
{
	recvCnt = 0;

	TestPck pck;
	pck.val = 10;
	pck.list.push_back(L"Hello World!!!");
	pck.list.push_back(L"Hello Noob Project!!!");
	pck.list.push_back(L"Hello Noob Network!!!");

	startTime = ::Noob::GetNow();

	Send(pck);
}

void TestClient::OnRecv(::Noob::PacketPtr pck)
{
	::Noob::PacketDispatcher<TestClient>::Call(this, pck);
}

void TestClient::OnClose()
{

}

REGISTER_PCK_PROC( TestClient, TestPck )
void TestClient::OnPacket(const ::Noob::Ptr<TestPck>& pck)
{
	++recvCnt;

	if (recvCnt >= 1000)
	{
		::Noob::Duration elapse = ::Noob::GetNow() - startTime;
		::std::wstring resultMsg = ::std::wstring(L"ElapseTime : ") + ::std::to_wstring( ::Noob::TickToFloat(elapse.count()) ) + L"Sec";
		Logger::WriteMessage(resultMsg.c_str());

		SetEvent(g_TestCompleteEvent);
	}
	else
	{
		Send(pck);
	}
}
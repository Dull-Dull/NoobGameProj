#include "pch.h"
#include "TestServer.h"
#include "CppUnitTest.h"

#include "TestPck/Pck.h"
#include <NoobEngine/PacketDispatcher.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

::std::unordered_set< TestServerPtr > TestServer::container;

TestServer::TestServer(::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher) : IUser( session, dispatcher ){}

void TestServer::OnAccept()
{
	Logger::WriteMessage(L"Accept Test Client");
	container.insert(this);
}

void TestServer::OnRecv(::Noob::PacketPtr pck)
{
	::Noob::PacketDispatcher<TestServer>::Call(this, pck);
}

void TestServer::OnClose()
{
	container.erase(this);
}

REGISTER_PCK_PROC(TestServer, TestPck)
void TestServer::OnPacket(const ::Noob::Ptr<TestPck>& pck)
{
	Send(pck);
}
#include "pch.h"
#include "TestServer.h"

#include "TestPck/Pck.h"
#include <NoobEngine/PacketDispatcher.h>

TestServer::TestServer(::Noob::TcpSessionPtr session, ::Noob::Dispatcher* dispatcher){}

void TestServer::OnAccept()
{

}

void TestServer::OnRecv(::Noob::PacketPtr pck)
{

}

void TestServer::OnClose()
{

}
#include "pch.h"
#include "CppUnitTest.h"

#include "TestPck/PckRegister.h"
#include "TestClient.h"
#include "TestServer.h"
#include <NoobEngine/TcpSessionAcceptor.h>
#include <NoobEngine/TcpSessionConnector.h>
#include <NoobEngine/DispatcherSelector.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NoobUnitTest
{
	TEST_CLASS(NoobNetwork)
	{
	public:
		TEST_CLASS_INITIALIZE(Initialize)
		{
			initor = new ::Noob::WinSockInitor();
			iocp = new ::Noob::Iocp;

			iocp->Start();
		}

		TEST_CLASS_CLEANUP(Cleanup)
		{
			iocp->Stop();

			SAFE_DELETE(iocp);
			SAFE_DELETE(initor);
		}

		TEST_METHOD(PingPongPerformance)
		{
			ResetEvent(g_TestCompleteEvent);

			::Noob::Listener listener( iocp, ::Noob::EndPoint( INADDR_ANY, 12345 ));
			::Noob::Acceptor< TestServer, ::Noob::SingleThreadDispatcher >* acceptor =
				new ::Noob::Acceptor< TestServer, ::Noob::SingleThreadDispatcher >( iocp, &listener );
			acceptor->Post();

			::Noob::Connector< TestClient, ::Noob::SingleThreadDispatcher >* connector = 
				new ::Noob::Connector< TestClient, ::Noob::SingleThreadDispatcher >();
			connector->Connect(iocp, ::Noob::EndPoint(L"127.0.0.1", 12345));

			DWORD result = WaitForSingleObject(g_TestCompleteEvent, 10000);

			if (result == WAIT_TIMEOUT)
			{
				Assert::Fail(L"TestTimeout");
			}
		}

		static ::Noob::MiniDump dump;
		static ::Noob::WinSockInitor* initor;		
		static ::Noob::Iocp* iocp;
	};

	::Noob::MiniDump NoobNetwork::dump;
	::Noob::WinSockInitor* NoobNetwork::initor = nullptr;
	::Noob::Iocp* NoobNetwork::iocp = nullptr;
}

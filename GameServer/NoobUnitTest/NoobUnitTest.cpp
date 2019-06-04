#include "pch.h"
#include "CppUnitTest.h"

#include "TestPck/PckRegister.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NoobUnitTest
{
	TEST_CLASS(NoobUnitTest)
	{
	public:
		TEST_CLASS_INITIALIZE(Initialize)
		{
			::Noob::MiniDump dump;

			::Noob::WinSockInitor* initor = new ::Noob::WinSockInitor();
			::Noob::Iocp* iocp = new ::Noob::Iocp;

			iocp->Start();
		}

		TEST_CLASS_CLEANUP(Cleanup)
		{
			iocp->Stop();

			SAFE_DELETE(iocp);
			SAFE_DELETE(initor);
		}


		TEST_METHOD(TestMethod1)
		{
			//TestTest!!@1#!#!
		}

		static ::Noob::MiniDump dump;
		static ::Noob::WinSockInitor* initor;		
		static ::Noob::Iocp* iocp;
	};

	::Noob::MiniDump NoobUnitTest::dump;
	::Noob::WinSockInitor* NoobUnitTest::initor = nullptr;
	::Noob::Iocp* NoobUnitTest::iocp = nullptr;

}

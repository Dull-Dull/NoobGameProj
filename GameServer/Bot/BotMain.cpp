#include "PreCompiled.h"

int main()
{
	::Noob::MiniDump dump;

	::Noob::WinSockInitor initor;
	::Noob::IocpPtr iocp = new ::Noob::Iocp;

	iocp->Start();


	iocp->Wait();

	return 0;
}
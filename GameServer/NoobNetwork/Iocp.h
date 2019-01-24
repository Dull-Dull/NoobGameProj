#pragma once

namespace Noob
{

class Iocp : public RefCnt
{
public:
				Iocp();
	virtual		~Iocp();

	void		Start(int threadNum = 0);
	void		Stop();
	void		Wait();

	void		Register( SOCKET sock );

private:
	static DWORD WINAPI ThreadFunc( void* arg );

private:
	HANDLE		iocpHandle;

	std::vector<HANDLE> threadHandleContainer;
	std::vector<DWORD>	threadIdContainer;
};
using IocpPtr = Ptr<Iocp>;

}
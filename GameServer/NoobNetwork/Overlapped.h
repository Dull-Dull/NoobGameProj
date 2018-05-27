#pragma once

namespace Noob
{

struct Overlapped : public WSAOVERLAPPED
{
	enum class IO_TYPE : int
	{
		SEND,
		RECV,
		ACCEPT,
		CONNECT,
	};

	Overlapped( IO_TYPE _ioType, const RefCntPtr& _object )
		: ioType( _ioType ), object( _object )
	{
		Init();
	}

	void Init()
	{
		ZeroMemory( this, sizeof( WSAOVERLAPPED ) );
	}

	IO_TYPE		ioType;
	RefCntPtr	object;
};

}
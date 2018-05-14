#include "PreCompiled.h"
#include "MiniDump.h"

#include <Windows.h>
#include <thread>

#pragma warning( push )
#pragma warning( disable : 4091 )
#include <DbgHelp.h>
#pragma warning( pop )

#pragma comment( lib, "DbgHelp.Lib" )

namespace Noob
{

std::wstring GetFileName()
{
	SYSTEMTIME sysTime;
	GetSystemTime( &sysTime );

	wchar fileName[512] = { 0, };
	wsprintfW( fileName, L"%4d_%2d_%2d_%2d_%2d.dmp", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute );

	return fileName;
}

void WriteDump( _EXCEPTION_POINTERS* exceptionInfo )
{
	MINIDUMP_EXCEPTION_INFORMATION MinidumpExceptionInformation;

	MinidumpExceptionInformation.ThreadId = ::GetCurrentThreadId();
	MinidumpExceptionInformation.ExceptionPointers = exceptionInfo;
	MinidumpExceptionInformation.ClientPointers = FALSE;

	HANDLE hDumpFile = ::CreateFileW( GetFileName().c_str(),
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL );

	if( hDumpFile!=INVALID_HANDLE_VALUE )
	{
		MiniDumpWriteDump(GetCurrentProcess(),
			GetCurrentProcessId(),
			hDumpFile,
			MiniDumpNormal,
			&MinidumpExceptionInformation,
			NULL,
			NULL);
	}
}

LONG WINAPI UnHandledExceptionFilter( _EXCEPTION_POINTERS* exceptionInfo )
{
	if( exceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW )
	{
		std::thread t1( WriteDump, exceptionInfo );
		t1.join();
	}
	else
	{
		WriteDump( exceptionInfo );
	}
	
	::TerminateProcess( ::GetCurrentProcess(), 0 );

	return 0;
}

struct MiniDump::imple
{
	LPTOP_LEVEL_EXCEPTION_FILTER preFilter;
};

MiniDump::MiniDump() : pImple( new imple )
{
	SetErrorMode( SEM_FAILCRITICALERRORS );

	pImple->preFilter = SetUnhandledExceptionFilter( UnHandledExceptionFilter );
}

MiniDump::~MiniDump()
{
	SetUnhandledExceptionFilter( pImple->preFilter );
}

}
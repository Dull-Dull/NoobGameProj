#include "PreCompiled.h"
#include "LogThread.h"

#include "LogStream.h"
#include "TaskQueue.hpp"
#include <thread>
#include <Windows.h>
#include <locale.h>

namespace Noob
{

class LogThread::Imple
{
public:
	TaskQueue<LogStream> taskQueue;
	HANDLE fileHandle;
	HANDLE threadHandle;
	DWORD threadID;

public:
	Imple( ::std::wstring&& fileName );
	static DWORD WINAPI ThreadFunc( void* arg );
};

LogThread::Imple::Imple( ::std::wstring&& fileName ) : fileHandle( NULL ), threadHandle( NULL ), threadID( 0 )
{
	wchar currentPath[MAX_PATH] = {0,};
	GetCurrentDirectoryW( MAX_PATH, currentPath );

	::std::wstring path;
	path += currentPath;
	path += L"\\Log";
	_wmkdir( path.c_str() );

	path += L"\\";
	path += fileName;

	fileHandle = CreateFileW( path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if( fileHandle == INVALID_HANDLE_VALUE )
	{
		DWORD lastError = ::GetLastError();
		::std::wstring msg = fileName;
		msg += L" 파일을 열 수 없습니다.\nErrorCode : ";
		msg += ::std::to_wstring( lastError );
		MessageBoxW( NULL, msg.c_str(), 0, 0 );
		exit( -1 );
	}

	unsigned short mark = 0xFEFF;
	DWORD writtenBytes = 0;
	::WriteFile( fileHandle, &mark, sizeof(mark), &writtenBytes, NULL);

	SetFilePointer( fileHandle, 0, NULL, FILE_END );

	threadHandle = CreateThread( NULL, 0, ThreadFunc, this, 0, &threadID );
	if( threadHandle==INVALID_HANDLE_VALUE )
	{
		DWORD lastError = ::GetLastError();
		::std::wstring msg = fileName;
		msg += L" 쓰래드 생성 실패.\nErrorCode : ";
		msg += ::std::to_wstring( lastError );
		MessageBoxW( NULL, msg.c_str(), 0, 0 );
		exit( -1 );
	}
}

LogThread::LogThread( ::std::wstring&& fileName )
{
	pImple = new Imple( ::std::move( fileName ) );
}

LogThread::~LogThread()
{
	pImple->taskQueue.Push( nullptr );
	WaitForSingleObject( pImple->threadHandle, 1000 );
	CloseHandle( pImple->fileHandle );
	delete pImple;
}

void LogThread::Post( LogStream* stream )
{
	pImple->taskQueue.Push( stream );
}

DWORD WINAPI LogThread::Imple::ThreadFunc( void* arg )
{
	LogThread::Imple* pImple = reinterpret_cast<LogThread::Imple*>( arg );

	LogStream* stream;

	while( pImple->taskQueue.Pop( stream ) )
	{
		if( stream == nullptr )
			return 0;

		DWORD numOfWriteByte = 0;

		stream->GetBuf().append( L"\r\n" );

		WriteFile( pImple->fileHandle,
			stream->GetBuf().c_str(),
			(DWORD)( stream->GetBuf().length() ) * sizeof( ::std::wstring::value_type ),
			&numOfWriteByte,
			NULL );

		delete stream;
	}

	return 0;
}

}
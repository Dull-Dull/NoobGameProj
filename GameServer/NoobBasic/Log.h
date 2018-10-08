#pragma once

#include "LogStream.h"
#include "LogThread.h"

#ifdef ERROR
#undef ERROR
#endif

namespace Noob
{

enum class LOG_TYPE : int
{
	CONSOLE,
	INFO,
	WARNING,
	ERROR,
};

extern LogThread* const infoLogThread;
extern LogThread* const warningLogThread;
extern LogThread* const errorLogThread;



template < typename Type >
void __Log( LogStream& stream, const Type& val )
{
	stream << val;
}

template< typename Type, typename ... Args >
void __Log( LogStream& stream, const Type& val, const Args&... args )
{
	stream << val << L"\t";
	__Log( stream, args... );
}

template< typename ...  Args >
void Log( LOG_TYPE type, const Args&... args )
{
	LogStream* stream = new LogStream;

	stream->SetNowTime();
	__Log( *stream, args... );

	switch( type )
	{
	case LOG_TYPE::CONSOLE :
		wprintf( L"%s\n", stream->GetBuf().c_str() );
		break;
	case LOG_TYPE::INFO :
		infoLogThread->Post( stream );
		break;
	case LOG_TYPE::WARNING :
		warningLogThread->Post( stream );
		break;
	case LOG_TYPE::ERROR :
		wprintf( L"%s\n", stream->GetBuf().c_str() );
		errorLogThread->Post( stream );
		break;
	}
}

}

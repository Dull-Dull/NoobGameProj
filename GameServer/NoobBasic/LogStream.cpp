#include "PreCompiled.h"
#include "LogStream.h"

#include "LogAble.h"
#include <Windows.h>

void LogStream::SetNowTime()
{
	SYSTEMTIME sysTime;
	GetSystemTime( &sysTime );

	wchar nowTime[32] = { 0, };
	wsprintfW( nowTime, L"[%4d-%02d-%02d %02d:%02d:%02d.%03d]",
		sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds );

	*this << nowTime;
}

LogStream & LogStream::operator<<( const ::Noob::LogAble & val )
{
	val.Logging( *this );
	return *this;
}

LogStream & LogStream::operator<<( const int & val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const unsigned int & val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const __int64 & val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const unsigned __int64 & val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const long& val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const unsigned long& val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const short & val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const unsigned short & val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const byte & val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const bool & val )
{
	buf += val ? L"true" : L"false";
	return *this;
}

LogStream & LogStream::operator<<( const float & val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const double & val )
{
	buf += std::to_wstring( val );
	return *this;
}

LogStream & LogStream::operator<<( const std::wstring & val )
{
	buf += val;
	return *this;
}

LogStream & LogStream::operator<<( const wchar * val )
{
	buf += val;
	return *this;
}

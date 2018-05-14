#pragma once

namespace Noob
{
class LogAble;
}

class LogStream
{
public:
	LogStream& operator << ( const ::Noob::LogAble& val );
	LogStream& operator << ( const int& val );
	LogStream& operator << ( const unsigned int& val );
	LogStream& operator << ( const __int64& val );
	LogStream& operator << ( const unsigned __int64& val );
	LogStream& operator << ( const long& val );
	LogStream& operator << ( const unsigned long& val );
	LogStream& operator << ( const short& val );
	LogStream& operator << ( const unsigned short& val );
	LogStream& operator << ( const byte& val );
	LogStream& operator << ( const bool& val );
	LogStream& operator << ( const float& val );
	LogStream& operator << ( const double& val );
	LogStream& operator << ( const std::wstring& val );
	LogStream& operator << ( const wchar* val );

	void SetNowTime();
	std::wstring& GetBuf(){ return buf; }
private:
	std::wstring buf;
};
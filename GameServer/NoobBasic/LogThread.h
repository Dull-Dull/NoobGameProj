#pragma once

class LogStream;

namespace Noob
{

class LogThread
{
public:
	LogThread( std::wstring&& fileName );
	virtual ~LogThread();

	void Post( LogStream* stream );
private:
	class Imple;
	Imple* pImple;
};

}

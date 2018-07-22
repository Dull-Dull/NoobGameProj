#pragma once


struct SC_Hello : public ::Noob::Packet
{
	SC_Hello()
	{
		index = 1;
	}

	std::wstring GetName(){ return L"SC_Hello"; }
	static unsigned int GetIndex(){ return 1; }
};

inline StreamReader& operator>>( StreamReader& stream, SC_Hello& val )
{
	return stream;
}

inline StreamWriter& operator<<( StreamWriter& stream, SC_Hello& val )
{
	return stream;
}

struct CS_Hello : public ::Noob::Packet
{
	CS_Hello()
	{
		index = 2;
	}

	std::wstring GetName(){ return L"CS_Hello"; }
	static unsigned int GetIndex(){ return 2; }
};

inline StreamReader& operator>>( StreamReader& stream, CS_Hello& val )
{
	return stream;
}

inline StreamWriter& operator<<( StreamWriter& stream, CS_Hello& val )
{
	return stream;
}

struct SC_Ping : public ::Noob::Packet
{
	int64_t tick;

	SC_Ping()
	{
		index = 3;
	}

	SC_Ping( int64_t _tick )
	{
		index = 3;
		tick = _tick;
	}

	std::wstring GetName(){ return L"SC_Ping"; }
	static unsigned int GetIndex(){ return 3; }
};

inline StreamReader& operator>>( StreamReader& stream, SC_Ping& val )
{
	return stream>>val.tick;
}

inline StreamWriter& operator<<( StreamWriter& stream, SC_Ping& val )
{
	return stream<<val.tick;
}

struct CS_Ping : public ::Noob::Packet
{
	int64_t tick;

	CS_Ping()
	{
		index = 4;
	}

	CS_Ping( int64_t _tick )
	{
		index = 4;
		tick = _tick;
	}

	std::wstring GetName(){ return L"CS_Ping"; }
	static unsigned int GetIndex(){ return 4; }
};

inline StreamReader& operator>>( StreamReader& stream, CS_Ping& val )
{
	return stream>>val.tick;
}

inline StreamWriter& operator<<( StreamWriter& stream, CS_Ping& val )
{
	return stream<<val.tick;
}

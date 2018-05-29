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

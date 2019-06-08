#pragma once


struct TestPck : public ::Noob::Packet
{
	int val;
	::std::vector<::std::wstring> list;

	TestPck()
	{
		index = 1;
	}

	TestPck( int _val, ::std::vector<::std::wstring> _list )
	{
		index = 1;
		val = _val;
		list = _list;
	}

	::std::wstring GetName(){ return L"TestPck"; }
	static unsigned int GetIndex(){ return 1; }
};

inline StreamReader& operator>>( StreamReader& stream, TestPck& val )
{
	return stream>>val.val>>val.list;
}

inline StreamWriter& operator<<( StreamWriter& stream, TestPck& val )
{
	return stream<<val.val<<val.list;
}

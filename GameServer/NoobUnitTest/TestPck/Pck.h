#pragma once


struct TestPck1 : public ::Noob::Packet
{
	int val1;
	int val2;
	int val3;
	::std::vector<int> list;

	TestPck1()
	{
		index = 1;
	}

	TestPck1( int _val1, int _val2, int _val3, ::std::vector<int> _list )
	{
		index = 1;
		val1 = _val1;
		val2 = _val2;
		val3 = _val3;
		list = _list;
	}

	::std::wstring GetName(){ return L"TestPck1"; }
	static unsigned int GetIndex(){ return 1; }
};

inline StreamReader& operator>>( StreamReader& stream, TestPck1& val )
{
	return stream>>val.val1>>val.val2>>val.val3>>val.list;
}

inline StreamWriter& operator<<( StreamWriter& stream, TestPck1& val )
{
	return stream<<val.val1<<val.val2<<val.val3<<val.list;
}

struct TestPck2 : public ::Noob::Packet
{
	int val1;

	TestPck2()
	{
		index = 2;
	}

	TestPck2( int _val1 )
	{
		index = 2;
		val1 = _val1;
	}

	::std::wstring GetName(){ return L"TestPck2"; }
	static unsigned int GetIndex(){ return 2; }
};

inline StreamReader& operator>>( StreamReader& stream, TestPck2& val )
{
	return stream>>val.val1;
}

inline StreamWriter& operator<<( StreamWriter& stream, TestPck2& val )
{
	return stream<<val.val1;
}

struct TestData3
{
	int val1;
	::std::wstring val2;

	static ::std::wstring GetName(){ return L"TestData3"; }
};

inline StreamReader& operator>>( StreamReader& stream, TestData3& val )
{
	return stream>>val.val1>>val.val2;
}

inline StreamWriter& operator<<( StreamWriter& stream, TestData3& val )
{
	return stream<<val.val1<<val.val2;
}

#pragma once

const static size_t DEFAULT_STREAM_BUFF_SIZE = 4096;

struct StreamBuf
{
	StreamBuf( size_t bufSize = DEFAULT_STREAM_BUFF_SIZE )
	{
		m_rowBuf = new byte[bufSize];
		m_bufSize = bufSize;
		m_externBuf = false;
	}

	StreamBuf( byte* buf, size_t bufSize )
	{
		m_rowBuf = buf;
		m_bufSize = bufSize;
		m_externBuf = true;
	}

	~StreamBuf()
	{
		if( m_externBuf == false )
			delete [] m_rowBuf;
	}

	void ReAlloc()
	{
		assert( m_externBuf == false );

		byte* tempBuffer = m_rowBuf;
		m_rowBuf = new byte[ m_bufSize * 2 ];
		memcpy( m_rowBuf, tempBuffer, m_bufSize );
		m_bufSize *= 2;
	}
	byte*	m_rowBuf;
	size_t	m_bufSize;
	bool	m_externBuf;
};

struct StreamReader
{
	StreamReader( StreamBuf& buffer ) : m_buffer( buffer ), m_offSet( 0 ){}
	inline byte* GetNowBuffer(){ return m_buffer.m_rowBuf + m_offSet; }

	StreamBuf& m_buffer;
	unsigned int m_offSet;

	template< typename BasicType >
	StreamReader& operator>>( BasicType& val )
	{
		static_assert( std::is_arithmetic<BasicType>::value, "Invalid Type" );
		memcpy( &val, GetNowBuffer(), sizeof( BasicType ) );
		m_offSet += sizeof( BasicType );

		return *this;
	}

	template< typename BasicType >
	StreamReader& operator>>( const BasicType& val )
	{
		static_assert( std::is_arithmetic<BasicType>::value, "Invalid Type" );
		BasicType& nonConstVal = const_cast<BasicType&>(val);

		memcpy( &nonConstVal, GetNowBuffer(), sizeof( BasicType ) );
		m_offSet += sizeof( BasicType );

		return *this;
	}

	template< typename DataType >
	StreamReader& operator>>( std::vector< DataType >& val )
	{
		static_assert( !std::is_same<bool, DataType>::value, "Can't Serializing std::vector<bool>" );
		val.clear();

		unsigned int vecSize = 0;
		*this >> vecSize;

		for( unsigned int i = 0; i < vecSize; ++i )
		{
			DataType tempData;
			*this >> tempData;
			val.push_back( tempData );
		}			

		return *this;
	}

	template< typename DataType >
	StreamReader& operator>>( std::set< DataType >& val )
	{
		val.clear();

		unsigned int setSize = 0;
		*this >> setSize;

		for( unsigned int i = 0; i < setSize; ++i )
		{
			DataType tempData;
			*this >> tempData;
			val.insert( tempData );
		}			

		return *this;
	}

	template< typename Key, typename Value >
	StreamReader& operator>>( std::pair< Key, Value >& val )
	{
		*this >> val.first >> val.second;
		return *this;
	}

	template< typename Key, typename Value >
	StreamReader& operator>>( std::map< Key, Value >& val )
	{
		val.clear();

		unsigned int mapSize = 0;
		*this >> mapSize;

		for( unsigned int i = 0; i < mapSize; ++i )
		{
			std::map< Key, Value >::value_type tempData;
			*this >> tempData;
			val.insert( tempData );
		}			

		return *this;
	}

	template<>
	StreamReader& operator>>( std::wstring& val )
	{
		unsigned int strSize = 0;
		*this >> strSize;

		wchar* str = reinterpret_cast<wchar*>( GetNowBuffer() );
		*( str + strSize ) = L'\0';

		val = str;
		m_offSet += ( strSize + 1 ) * sizeof( wchar );

		return *this;
	}

	template<>
	StreamReader& operator>>( std::string& val )
	{
		unsigned int strSize = 0;
		*this >> strSize;

		char* str = reinterpret_cast<char*>( GetNowBuffer() );
		*( str + strSize ) = '\0';

		val = str;
		m_offSet += ( strSize + 1 ) * sizeof( char );

		return *this;
	}
};

struct StreamWriter
{
	StreamWriter( StreamBuf& buffer ) : m_buffer( buffer ), m_offSet( 0 ){}
	inline byte* GetNowBuffer(){ return m_buffer.m_rowBuf + m_offSet; }

	StreamBuf& m_buffer;
	unsigned int m_offSet;

	template< typename BasicType >
	StreamWriter& operator<<( const BasicType& val )
	{
		static_assert( std::is_arithmetic<BasicType>::value, "Invalid Type" );

		if( m_buffer.m_bufSize < m_offSet + sizeof( BasicType ) )
			m_buffer.ReAlloc();

		memcpy( GetNowBuffer(), &val, sizeof( BasicType ) );
		m_offSet += sizeof( BasicType );

		return *this;
	}

	template< typename DataType >
	StreamWriter& operator<<( const std::vector< DataType >& val )
	{
		unsigned int vecSize = static_cast<unsigned int>( val.size() );
		*this << vecSize;

		for( auto& tempData : val )
			*this << tempData;

		return *this;
	}

	template< typename DataType >
	StreamWriter& operator<<( const std::set< DataType >& val )
	{
		unsigned int setSize = static_cast<unsigned int>( val.size() );
		*this << setSize;

		for( std::set< DataType >::iterator i = val.begin() ; i != val.end() ; ++i )
			*this << *i;

		return *this;
	}

	template< typename Key, typename Value >
	StreamWriter& operator<<( const std::pair< Key, Value >& val )
	{
		return *this << val.first << val.second;
	}

	template< typename Key, typename Value >
	StreamWriter& operator<<( const std::map< Key, Value >& val )
	{
		unsigned int mapSize = static_cast<unsigned int>( val.size() );
		*this << mapSize;

		for( auto& tempData : val )
			*this << tempData;

		return *this;
	}

	template<>
	StreamWriter& operator<<( const std::wstring& val )
	{
		unsigned int strSize = static_cast<unsigned int>( val.size() );
		*this << strSize;

		if( m_buffer.m_bufSize < ( m_offSet + ( strSize + 1 ) * sizeof( wchar ) ) )
			m_buffer.ReAlloc();

		memcpy( GetNowBuffer(), val.c_str(), ( strSize + 1 ) * sizeof( wchar ) );
		m_offSet += ( strSize + 1 ) * sizeof( wchar );

		return *this;
	}

	template<>
	StreamWriter& operator<<( const std::string& val )
	{
		unsigned int strSize = static_cast<unsigned int>( val.size() );
		*this << strSize;

		if( m_buffer.m_bufSize < ( m_offSet + ( strSize + 1 ) * sizeof( char ) ) )
			m_buffer.ReAlloc();

		memcpy( GetNowBuffer(), val.c_str(), ( strSize + 1 ) * sizeof( char ) );
		m_offSet += ( strSize + 1 ) * sizeof( char );

		return *this;
	}
};
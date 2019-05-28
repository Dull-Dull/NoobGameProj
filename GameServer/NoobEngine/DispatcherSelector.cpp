#include "PreCompiled.h"
#include "DispatcherSelector.h"

namespace Noob
{
SingleThreadDispatcher::SingleThreadDispatcher() : m_dispatcher( new Dispatcher() ){}

SingleThreadDispatcher::~SingleThreadDispatcher()
{
	SAFE_DELETE( m_dispatcher);
}

RRDispatcher::RRDispatcher()
{
	SYSTEM_INFO si = {};
	GetSystemInfo( &si );
	m_coreCnt = static_cast<size_t>( si.dwNumberOfProcessors );
	m_dispatchers.reserve( m_coreCnt );

	for( size_t i = 0; i < m_coreCnt; ++i )
		m_dispatchers.push_back( new Dispatcher() );

	m_index = 0;
}

RRDispatcher::~RRDispatcher()
{
	for( size_t i = 0 ; i < m_coreCnt; ++i )
		SAFE_DELETE( m_dispatchers[i] );
}

Dispatcher* RRDispatcher::Get()
{
	Dispatcher* dispatcher = m_dispatchers[m_index++];
	m_index %= m_coreCnt;
	return dispatcher;
}

}
#pragma once

#include <NoobBasic\Singletone.hpp>
#include "Dispatcher.h"

namespace Noob
{

class SingleThreadDispatcher : public Singletone< SingleThreadDispatcher >
{
public:
	SingleThreadDispatcher();
	~SingleThreadDispatcher();
	Dispatcher* Get(){ return m_dispatcher; }
private:
	Dispatcher* m_dispatcher;
};

class RRDispatcher : public Singletone< RRDispatcher >
{
public:
	RRDispatcher();
	~RRDispatcher();
	Dispatcher* Get();

private:
	::std::vector<Dispatcher*> m_dispatchers;
	size_t m_index;
	size_t m_coreCnt;
};

}
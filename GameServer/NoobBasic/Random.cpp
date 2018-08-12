#include "PreCompiled.h"
#include "Random.h"

#include "Time.h"

namespace Noob
{

thread_local ::std::default_random_engine Random::m_engine( static_cast<unsigned>( GetTick() ) );

}
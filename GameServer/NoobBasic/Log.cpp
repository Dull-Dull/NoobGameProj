#include "PreCompiled.h"
#include "Log.h"

namespace Noob
{

LogThread* const infoLogThread		= new LogThread( L"Info.log" );
LogThread* const warningLogThread	= new LogThread( L"Warning.log" );
LogThread* const errorLogThread		= new LogThread( L"Error.log" );

}
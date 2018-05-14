#include "PreCompiled.h"
#include "RefCnt.h"
#include <Windows.h>

namespace Noob
{

void RefCnt::IncCnt()
{
	InterlockedIncrement(&refCnt);
}

void RefCnt::DecCnt()
{
	InterlockedDecrement(&refCnt);
}

unsigned int RefCnt::GetRefCnt()
{
	return refCnt;
}

}
#pragma once

#include "LogStream.h"

namespace Noob
{

class LogAble
{
public:
	virtual void Logging( LogStream& stream ) const = 0;
};

}
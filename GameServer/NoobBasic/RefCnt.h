#pragma once

namespace Noob
{

class RefCnt
{
public:
	virtual ~RefCnt(){}

	void IncCnt();
	void DecCnt();

	unsigned int GetRefCnt();

private:
	unsigned int refCnt = 0;
};

}
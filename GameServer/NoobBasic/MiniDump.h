#pragma once

namespace Noob
{

class MiniDump
{
public:
	MiniDump();
	~MiniDump();

private:
	struct imple;
	std::unique_ptr<imple> pImple;
};

}
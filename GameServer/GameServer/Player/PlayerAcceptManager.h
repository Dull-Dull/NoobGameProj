#pragma once

class PlayerAcceptManager
{
public:
	PlayerAcceptManager( ::Noob::Iocp* iocp, short port );
	~PlayerAcceptManager();

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};
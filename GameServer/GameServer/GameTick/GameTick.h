#pragma once

class GameDispatcher;

class GameTick
{
public:
	GameTick( GameDispatcher* pDispatcher );
	~GameTick();

private:
	struct imple;
	::std::unique_ptr<imple> pImple;

};
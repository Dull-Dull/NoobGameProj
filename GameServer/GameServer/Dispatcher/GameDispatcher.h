#pragma once

enum class E_GAME_TASK
{
	ACCEPT,
	CONNECT,
	RECV,
	CLOSE,
};

struct GameTask
{
	E_GAME_TASK m_eTask;
	::Noob::RefCnt m_obj;
};

class GameDispatcher
{
public:
	GameDispatcher();
	~GameDispatcher();

	void Push( E_GAME_TASK eTask, const ::Noob::RefCnt& obj );

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};
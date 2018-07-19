#pragma once

enum class E_GAME_TASK
{
	ACCEPT,
	CONNECT,
	RECV,
	CLOSE,
	ALARM,
};

struct GameTask
{
	E_GAME_TASK m_eTask;
	::Noob::RefCntPtr m_obj;
};

class GameDispatcher : public ::Noob::Singletone< GameDispatcher >
{
public:
	GameDispatcher();
	~GameDispatcher();

	void Push( E_GAME_TASK eTask, const ::Noob::RefCntPtr& obj );

private:
	struct imple;
	::std::unique_ptr<imple> pImple;
};
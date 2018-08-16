#pragma once

//#include "Player.h"

DECL_CLASS( Player );

class PlayerContainer : public ::Noob::Singletone<PlayerContainer>
{
public:
	PlayerContainer();

	void Insert( const PlayerPtr& player );
	void Delete( const PlayerPtr& player );

	::std::unordered_set< PlayerPtr >::iterator begin();
	::std::unordered_set< PlayerPtr >::iterator end();
private:
	::std::unordered_set< PlayerPtr > container;
};
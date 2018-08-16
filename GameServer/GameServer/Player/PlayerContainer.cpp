#include "PreCompiled.h"
#include "PlayerContainer.h"

#include "Player.h"

PlayerContainer::PlayerContainer()
{

}

void PlayerContainer::Insert( const PlayerPtr& player )
{
	container.insert( player );
}

void PlayerContainer::Delete( const PlayerPtr& player )
{
	container.erase( player );
}

::std::unordered_set< PlayerPtr >::iterator PlayerContainer::begin()
{
	return container.begin();
}

::std::unordered_set< PlayerPtr >::iterator PlayerContainer::end()
{
	return container.end();
}
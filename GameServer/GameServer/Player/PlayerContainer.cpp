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
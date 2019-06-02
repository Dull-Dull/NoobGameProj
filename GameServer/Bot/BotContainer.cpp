#include "PreCompiled.h"
#include "BotContainer.h"
#include "Bot.h"

BotContainer::BotContainer()
{

}

void BotContainer::Insert( const BotPtr& bot )
{
	container.insert( bot );
}

void BotContainer::Delete( const BotPtr& bot )
{
	container.erase( bot );
}
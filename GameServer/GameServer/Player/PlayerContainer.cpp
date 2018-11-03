#include "PreCompiled.h"
#include "PlayerContainer.h"

#include "Player.h"

PlayerIterator::PlayerIterator( ::std::unordered_map< unsigned int, PlayerPtr >::iterator iter )
{
	m_iter = iter;
}

PlayerPtr& PlayerIterator::operator * () const
{
	return m_iter->second;
}

PlayerIterator& PlayerIterator::operator ++ ()
{
	++m_iter;
	return *this;
}

bool PlayerIterator::operator == ( PlayerIterator rhs ) const
{
	return m_iter == rhs.m_iter;
}

bool PlayerIterator::operator != ( PlayerIterator rhs ) const
{
	return m_iter != rhs.m_iter;
}

PlayerContainer::PlayerContainer()
{

}

void PlayerContainer::Insert( const PlayerPtr& player )
{
	container.emplace( player->GetIndex(), player );
}

void PlayerContainer::Delete( const PlayerPtr& player )
{
	container.erase( player->GetIndex() );
}

PlayerPtr PlayerContainer::Find( unsigned int index )
{
	auto iter = container.find( index );
	if( iter == container.end() )
		return nullptr;
	else
		return iter->second;
}

PlayerIterator PlayerContainer::begin()
{
	return container.begin();
}

PlayerIterator PlayerContainer::end()
{
	return container.end();
}
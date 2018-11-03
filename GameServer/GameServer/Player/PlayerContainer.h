#pragma once

DECL_CLASS( Player );

class PlayerIterator
{
public:
	PlayerIterator( ::std::unordered_map< unsigned int, PlayerPtr >::iterator iter );

	PlayerPtr& operator * () const;
	PlayerIterator& operator ++ ();
	bool operator == ( PlayerIterator rhs ) const;
	bool operator != ( PlayerIterator rhs ) const;
private:
	::std::unordered_map< unsigned int, PlayerPtr >::iterator m_iter;
};

class PlayerContainer : public ::Noob::Singletone<PlayerContainer>
{
public:
	PlayerContainer();

	void Insert( const PlayerPtr& player );
	void Delete( const PlayerPtr& player );
	PlayerPtr Find( unsigned int index );

	PlayerIterator begin();
	PlayerIterator end();
private:
	::std::unordered_map< unsigned int, PlayerPtr > container;
};
#pragma once

DECL_CLASS( Bot );

class BotContainer : public ::Noob::Singletone<BotContainer>
{
public:
	BotContainer();

	void Insert( const BotPtr& bot );
	void Delete( const BotPtr& bot );

private:
	::std::unordered_set< BotPtr > container;
};
#pragma once
#include "Enemy.h"

class Skeleton :
	public Enemy
{

	void handleState();
	void handleEvent(Event e, Player& player);
	void create(Texture&, float, float);
	void changeSprite(State _state);
public:
	Skeleton();
	b2Body* GetPhysicsBody();
	void LoadContent();
	void Update(Event gameEvent, Player& player, Time dt, Time frameTime);
	void Draw(sf::RenderWindow& window, sf::Time dt);

	Skeleton* IamA(uint16 category) { _fixtureDef.filter.categoryBits = category; return this; }
	void ICollideWith(uint16 collisionPartners) { _fixtureDef.filter.maskBits = collisionPartners; }
};


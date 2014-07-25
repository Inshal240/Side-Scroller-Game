#pragma once
#include "Enemy.h"
class Kirby :
	public Enemy
{
	void handleState();
	void handleEvent(Event e, Player& player);
	void create(Texture&, float, float);
	void changeSprite(State _state);

public:
	Kirby();
	b2Body* GetPhysicsBody();
	void LoadContent();
	void Update(Event gameEvent, Player& player, Time dt, Time frameTime);
	void Draw(sf::RenderWindow& window, sf::Time dt);

	Kirby* IamA(uint16 category) { _fixtureDef.filter.categoryBits = category; return this; }
	void ICollideWith(uint16 collisionPartners) { _fixtureDef.filter.maskBits = collisionPartners; }
};


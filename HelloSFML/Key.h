#pragma once
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "MathHelper.h"

class Key
{


private:
	sf::Sprite		KeySprite;


	b2Body* _pBody;
	b2BodyDef _bodyDef;
	b2PolygonShape _bodyShape;
	b2FixtureDef _fixtureDef;

public:
	bool isCollected;
	Key();
	Key(sf::Texture& KeyTexture, float x, float y);
	void Create(sf::Texture& KeyTexture, float x, float y);
	~Key();


	void Draw(sf::RenderWindow& window, sf::Time dt);

	sf::Sprite& GetSprite();
	void SetWorld(b2World& world);

	Key* IamA(uint16 category) { _fixtureDef.filter.categoryBits = category; return this; }

	void ICollideWith(uint16 collisionPartners) { _fixtureDef.filter.maskBits = collisionPartners; }
	void Destroy(b2World& world);
	b2Body* GetPhysicsBody();

};


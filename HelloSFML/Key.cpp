#include "Key.h"

Key::Key(){}

Key::Key(sf::Texture& KeyTexture, float x, float y)
{
	isCollected = false;
	KeySprite.setTexture(KeyTexture);
	KeySprite.setOrigin(32, 32);
	KeySprite.setPosition(x, y);
	

	_bodyDef.position.Set(MathHelper::ToUnit(x), MathHelper::ToUnit(y));

	_bodyDef.type = b2_staticBody;

	_bodyShape.SetAsBox(MathHelper::ToUnit(16), MathHelper::ToUnit(16));

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 0.1f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.0f;
}

void Key::Create(sf::Texture& KeyTexture, float x, float y)
{
	
	isCollected = false;
	KeySprite.setTexture(KeyTexture);
	KeySprite.setOrigin(24, 24);
	KeySprite.setPosition(x, y);


	_bodyDef.position.Set(MathHelper::ToUnit(x), MathHelper::ToUnit(y));

	_bodyDef.type = b2_staticBody;

	_bodyShape.SetAsBox(MathHelper::ToUnit(12), MathHelper::ToUnit(12));

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 0.1f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.0f;

}



void Key::Draw(sf::RenderWindow& window, sf::Time dt)
{
	if (!isCollected)
		window.draw(KeySprite);
	
}
Key::~Key(void)
{
}

void Key::SetWorld(b2World& world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
	_pBody->SetUserData(this);
}
void Key::Destroy(b2World& world)
{
	_pBody->SetTransform(b2Vec2(MathHelper::ToUnit(4500), MathHelper::ToUnit(800)),0);
}
b2Body* Key::GetPhysicsBody()
{
	return _pBody;
}
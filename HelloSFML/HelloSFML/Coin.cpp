#include "Coin.h"


Coin::Coin() : _coinSprite(), _animSequence()
{
}

void Coin::Create(sf::Texture& coinTexture, float x, float y)
{
	//sprite sheet is 8x8 with 64x64 frames
	//_cointTest.setTexture(coinTexture);
	//_cointTest.setPosition( 40, 70);
	isCollected=false;
	
	_animSequence.setSpriteSheet( coinTexture );

	for ( int col = 0; col < 8; col++ )
	{
		for ( int row = 0; row < 8; row++ )
		{
			_animSequence.addFrame(sf::IntRect(row*64, col*64 , 64, 64 ));
			//_animSequence.addFrame(sf::IntRect(64 , 64, 64, 64 ));
		}
	}

	_coinSprite.setOrigin( 32,32);
	_coinSprite.setPosition(x,y);
	_coinSprite.setAnimation( _animSequence );
	_coinSprite.setLooped(true);
	_coinSprite.setFrameTime(sf::seconds(0.02));
	_coinSprite.play(_animSequence);

	_bodyDef.position.Set( MathHelper::ToUnit( x ), MathHelper::ToUnit( y ) ); 

	_bodyDef.type = b2_staticBody;
	
	_bodyShape.SetAsBox(MathHelper::ToUnit(16),MathHelper::ToUnit(16));

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.5f;

}

void Coin::Update(sf::Event e, sf::Time dt) 
{
	_coinSprite.update(dt);
}

void Coin::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw(_coinSprite );
	//window.draw( _cointTest );
}
Coin::~Coin(void)
{
}

void Coin::SetWorld(b2World& world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
	_pBody->SetUserData(this);
}

b2Body* Coin::GetPhysicsBody()
{
	return _pBody;
}
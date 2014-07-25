#include "TimedSpikes.h"


TimedSpikes::TimedSpikes(void)
{
}


TimedSpikes::~TimedSpikes(void)
{
}


void TimedSpikes::SetWorld(b2World & world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
}

TimedSpikes::TimedSpikes(sf::Texture& texture, float initX, float initY, int repeatTimes,float restitution)
{
	//StaticPlatform(texture, initX, initY, repeatTimes);
	
	_sprite.setTexture( texture );

	//texture will be repeated 'repeatTimes' times along X-direction
	_sprite.setTextureRect( IntRect( 0, 0, repeatTimes * texture.getSize().x, texture.getSize().y ) ) ;

	texture.setRepeated( true );
	
	_sprite.setOrigin( repeatTimes * texture.getSize().x / 2.f, texture.getSize().y / 2.f);

	_bodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) ); 

	//_bodyDef.angle = MathHelper::DegreeToRadian( rotation );

	_bodyDef.type = b2_staticBody;

	_bodyShape.SetAsBox( 
		MathHelper::ToUnit( repeatTimes * texture.getSize().x / 2.f ),
		MathHelper::ToUnit( texture.getSize().y / 2.f )
	);

	//cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;
	
	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = restitution;
	
	cycleClock.restart();

}

void TimedSpikes::Update( Event gameEvent, Time dt )
{
	float elapsed = cycleClock.getElapsedTime().asSeconds();

	int upDownTime = 4;

	if ( elapsed < 1 ) {  
		//move up

		_pBody->SetTransform( b2Vec2( _pBody->GetPosition().x , _pBody->GetPosition().y + MathHelper::ToUnit(5) ), 0 );
	
	}

	if ( elapsed > 1 && elapsed < 2)  {
		//idle
	
	}

	if ( elapsed > 2 && elapsed < 3 ) {

		//move down
		_pBody->SetTransform( b2Vec2( _pBody->GetPosition().x , _pBody->GetPosition().y - MathHelper::ToUnit(5) ), 0 );
	}

	if ( elapsed >3  && elapsed < 4 ) {
		//idle down
	}

	if ( elapsed > 4) {
		//restart cycel

		cycleClock.restart();
	}

	_sprite.setPosition(
			MathHelper::ToPixel( _pBody->GetPosition().x ) ,
			MathHelper::ToPixel( _pBody->GetPosition().y ) 
		);


}

void TimedSpikes::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw( _sprite );
}


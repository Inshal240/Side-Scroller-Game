#pragma once
#include "staticplatform.h"
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;
class TimedSpikes //:
	//public StaticPlatform
{
protected:

	b2Body* _pBody;
   b2BodyDef _bodyDef;
   b2PolygonShape _bodyShape;
   b2FixtureDef _fixtureDef;
   
   sf::Sprite _sprite;

public:

	Clock cycleClock;

	TimedSpikes(sf::Texture& texture, float initX, float initY, int repeatTimes,float restitution=0.3);

	TimedSpikes(void);

	~TimedSpikes(void);

	b2Body* GetPhysicsBody(); 
	  
   virtual void Update(sf::Event e, sf::Time dt);

   void Draw( sf::RenderWindow& window, sf::Time dt );

   sf::Sprite& GetSprite();
	
   virtual TimedSpikes* IamA( uint16 category ) { _fixtureDef.filter.categoryBits = category; return this; } 

	virtual void ICollideWith( uint16 collisionPartners ) {  _fixtureDef.filter.maskBits = collisionPartners; }

	void SetWorld(b2World & world);

};


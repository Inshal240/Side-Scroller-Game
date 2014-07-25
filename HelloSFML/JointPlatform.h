#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "MathHelper.h"

class JointPlatform
{
private:

   b2Body*			_pBody;
   b2BodyDef		_bodyDef;
   b2CircleShape	_bodyShape;
   b2FixtureDef		_fixtureDef;

   b2RevoluteJointDef		_jointDef;
   b2BodyDef		_jointBodyDef;
   b2Body*			_pJointBody;
   b2CircleShape	_jointBodyShape;
   b2FixtureDef		_jointFixtureDef;
   b2RevoluteJoint* _pJoint;
   
   sf::Sprite _jointBodySprite;
   sf::Sprite _sprite;

   bool _drawJoint;
public:

   JointPlatform(float width, float height);
   
   JointPlatform(sf::Texture& texture, sf::Texture& jointTexture, float initX, float initY, float rotation = 0);

   JointPlatform(sf::Texture& texture,  float initX, float initY, bool isCircular);

   JointPlatform();
   
   void SetWorld(b2World& world);
   
   b2Body* GetPhysicsBody(); 
      
   void Update(sf::Event e, sf::Time dt);

   void Draw( sf::RenderWindow& window, sf::Time dt );

   sf::Sprite& GetSprite();

   JointPlatform* IamA( uint16 category ) { _fixtureDef.filter.categoryBits = category; return this; } 
   
    void ICollideWith( uint16 collisionPartners ) {  _fixtureDef.filter.maskBits = collisionPartners; }

};

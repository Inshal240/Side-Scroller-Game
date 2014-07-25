#pragma once
#include "Friend.h"
class Man :
	public Friend
{
public:
	Man();
	~Man();
	void LoadContent();

	
	Man* IamA( uint16 category ) { _fixtureDef.filter.categoryBits = category; return this; } 

	void ICollideWith( uint16 collisionPartners ) {  _fixtureDef.filter.maskBits = collisionPartners; }

};

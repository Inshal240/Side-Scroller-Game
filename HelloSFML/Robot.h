#pragma once
#include "Friend.h"
class Robot :
	public Friend
{
public:
	void LoadContent();
	Robot();
	~Robot();

	Robot* IamA(uint16 category) { _fixtureDef.filter.categoryBits = category; return this; }
	void ICollideWith(uint16 collisionPartners) { _fixtureDef.filter.maskBits = collisionPartners; }
};



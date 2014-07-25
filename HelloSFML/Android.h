#pragma once
#include "Friend.h"
class Android :
	public Friend
{
public:
	Android();
	~Android();
	void LoadContent();

	Android* IamA(uint16 category) { _fixtureDef.filter.categoryBits = category; return this; }
	void ICollideWith(uint16 collisionPartners) { _fixtureDef.filter.maskBits = collisionPartners; }
};


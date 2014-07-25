#include "Enemy.h"
#include <iostream>
#include <map>
#include <string>
#include "Ball.h"

using namespace std;
using namespace sf;

void Enemy::Damage(int amount)
{
	if (_state != Hurt)
	{
		_health -= amount;

		if (_health == 0)
		{
			_alive = false;
		}
		else _hit = true;
	}
}

void Enemy::DamageByPlayer(Player::State playerState, int frame)
{
	if (playerState == Player::Attack1 && frame == 2)
	{
		Damage(10);
	}
	else if (playerState == Player::Attack2 && frame == 3)
	{
		Damage(15);
	}
	else if (playerState == Player::Attack3 && frame == 4)
	{
		Damage(20);
	}
}

void Enemy::Draw(RenderWindow& window, Time dt)
{
	window.draw(_animatedSprite);
}

Enemy::Enemy()
{
}

// Changes here
bool Enemy::IsDestroyed() const
{
	return _destroyed;
}

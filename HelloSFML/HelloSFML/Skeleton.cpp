#include "Skeleton.h"
using namespace sf;
using namespace std;

void Skeleton::changeSprite(State _state)
{
	switch (_state)
	{
	case Idle:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Idle];
		break;

	case Walking:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Walking];
		break;

	case Running:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Running];
		break;

	case Rising:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.1f));
		_currentAnimation = &_animationBank[Rising];
		break;

	case Falling:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Falling];
		break;

	case Attack:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.15f));
		_currentAnimation = &_animationBank[Attack];
		break;

	case Hurt:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.3f));
		_currentAnimation = &_animationBank[Hurt];
		break;

	case Dead:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Dead];
		break;

	default:
		break;
	}

	_animatedSprite.play();

}

void Skeleton::LoadContent()
{
	_health = *(new Health(50));
	_attackCalled = false;

	Texture texture;

	// Idle Animation
	texture.loadFromFile("Art\\Skeleton\\Idle.png");
	_textureBank.insert(pair<State, Texture>(Idle, texture));

	_animationBank[Idle].setSpriteSheet(_textureBank[Idle]);
	_animationBank[Idle].addFrame(IntRect(0, 0, 16, 51));

	// Walking Animation
	texture.loadFromFile("Art\\Skeleton\\Walk.png");
	_textureBank.insert(pair<State, Texture>(Walking, texture));
	
	_animationBank[Walking].setSpriteSheet(_textureBank[Walking]);
	_animationBank[Walking].addFrame(IntRect( 64, 0, 16, 51));
	_animationBank[Walking].addFrame(IntRect(125, 0, 148 - 125, 51));
	_animationBank[Walking].addFrame(IntRect(192, 0, 18, 51));
	_animationBank[Walking].addFrame(IntRect(257, 0, 16, 51));
	_animationBank[Walking].addFrame(IntRect(317, 0, 339 - 317, 51));
	_animationBank[Walking].addFrame(IntRect(384, 0, 401 - 384, 51));
	
	// Running Animation
	_animationBank[Running] = _animationBank[Walking];

	// Attack Animation
	texture.loadFromFile("Art\\Skeleton\\Attack.png");
	_textureBank.insert(pair<State, Texture>(Attack, texture));

	_animationBank[Attack].setSpriteSheet(_textureBank[Attack]);
	_animationBank[Attack].addFrame(IntRect(  0, 0,  21 -   0, 51));
	_animationBank[Attack].addFrame(IntRect( 65, 0,  85 -  65, 51));
	_animationBank[Attack].addFrame(IntRect(130, 0, 149 - 130, 51));

	// Rising and Falling
	_animationBank[Rising] = _animationBank[Idle];
	_animationBank[Falling] = _animationBank[Idle];

	// Hurt Animation
	_animationBank[Hurt] = _animationBank[Idle];

	// Death Animation
	texture.loadFromFile("Art\\Skeleton\\Dead.png");
	_textureBank.insert(pair<State, Texture>(Dead, texture));

	_animationBank[Dead].setSpriteSheet(_textureBank[Dead]);
	_animationBank[Dead].addFrame(IntRect(0, 0, 25 - 0, 40));
	_animationBank[Dead].addFrame(IntRect(51, 0, 106 - 0, 40));
	_animationBank[Dead].addFrame(IntRect(0, 0, 0, 0));
	_animationBank[Dead].addFrame(IntRect(51, 0, 106 - 0, 40));
	_animationBank[Dead].addFrame(IntRect(0, 0, 0, 0));
	_animationBank[Dead].addFrame(IntRect(51, 0, 106 - 0, 40));
	_animationBank[Dead].addFrame(IntRect(0, 0, 0, 0));
	_animationBank[Dead].addFrame(IntRect(51, 0, 106 - 0, 40));
	_animationBank[Dead].addFrame(IntRect(0, 0, 0, 0));
	_animationBank[Dead].addFrame(IntRect(0, 0, 0, 0));
	_animationBank[Dead].addFrame(IntRect(0, 0, 0, 0));
	_animationBank[Dead].addFrame(IntRect(0, 0, 0, 0));

	// Setting up the animated sprite
	_animatedSprite.setLooped(false);
	_animatedSprite.play();
	_animatedSprite.setFrameTime(sf::seconds(0.2f));

	_currentAnimation = &_animationBank[Idle];

	_animatedSprite.setAnimation(*_currentAnimation);

	create(_textureBank[Idle], 900, 500);
}

void Skeleton::create(Texture& texture, float initX, float initY)
{
	_bodyDef.position.Set(MathHelper::ToUnit(initX), MathHelper::ToUnit(initY));
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.fixedRotation = true;

	_bodyShape.SetAsBox(
		MathHelper::ToUnit(texture.getSize().x / 2),
		MathHelper::ToUnit(texture.getSize().y / 2)
		);

	_animatedSprite.setOrigin(
		texture.getSize().x / 2,
		texture.getSize().y / 2
		);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.3f;
}

void Skeleton::handleState()
{
	// Remember what the player's _state was in the previous update
	_previousState = _state;

	if (!_alive)
	{
		_state = Dead;
	}
	else
	{
		if (_hit)
		{
			_state = Hurt;
			_hit = false;
		}

		// If the Hurt animation is done, then make the character Idle again
		if (_state == Hurt && !_animatedSprite.isPlaying())
		{
			_state = Idle;
		}

		// Attacking logic
		if (_attackCalled)
		{
			_state = Attack;
			_attackCalled = false;
		}
		else if (_state == Attack && !_animatedSprite.isPlaying())
		{
			_state = Idle;
		}

		// Only allow normal movement if character is not recoiling from damage
		// or dying or attacking
		if (_state != Hurt && _state != Dead && _state != Attack)
		{
			// Change the current _state according to vertical events
			if (_pBody->GetLinearVelocity().y > 0.1)
			{
				_state = Falling;
			}
			else if (_pBody->GetLinearVelocity().y == 0)
			{
				_state = Idle;
			}
			else if (_pBody->GetLinearVelocity().y < -0.1)
			{
				_state = Rising;
			}

			// Judge whether the character is in air or not
			if (_state != Rising && _state != Falling) _inAir = false;
			else _inAir = true;

			// Change the current _state according to horizontal events
			if (!_inAir)
			{
				if (_pBody->GetLinearVelocity().x < -1.5)
				{
					_state = Running;
				}
				else if (_pBody->GetLinearVelocity().x < 0)
				{
					_state = Walking;
				}
				else if (_pBody->GetLinearVelocity().x > 0)
				{
					_state = Walking;
				}
				if (_pBody->GetLinearVelocity().x > 1.5)
				{
					_state = Running;
				}

				if (_pBody->GetLinearVelocity().x < -0.1) _movingForward = false;
				else if (_pBody->GetLinearVelocity().x > 0.1) _movingForward = true;
			}
		}
		// If movement is in neither of the dimensions and the player is just standing
	}
}

void Skeleton::handleEvent(Event gameEvent, Player& player)
{
	b2Vec2 position = _pBody->GetPosition();
	b2Vec2 playerPosition = player.GetPhysicsBody()->GetPosition();

	float distanceFromPlayer = distanceFromBody(player.GetPhysicsBody());

	if (distanceFromPlayer < 3.6 && player.IsAlive())
	{
		playerFound = true;
	}
	else
	{
		playerFound = false;
	}

	if (playerFound && !_inAir)
	{
		if ((playerPosition.x - position.x) > 0)
			playerOnRight = 1;
		else playerOnRight = -1;

		if (distanceFromPlayer > 0.6)
		{
			_pBody->SetLinearVelocity(b2Vec2(
				1.2 * playerOnRight,
				_pBody->GetLinearVelocity().y
				));
		}
		// Judge whether to attack or not with a chance of 1/55
		else if (distanceFromPlayer < 0.6)
		{
			int choice = rand() % 55;

			if (choice == 0)
			{
				_attackCalled = true;
			}
		}
	}
}

void Skeleton::Update(Event gameEvent, Player& player, Time dt, Time frameTime)
{
	if (_state != Hurt && _state != Dead) handleEvent(gameEvent, player);
	handleState();

	if (_state != _previousState)
	{
		changeSprite(_state);
		_animatedSprite.setAnimation(*_currentAnimation);
	}

	_animatedSprite.setPosition(
		MathHelper::ToPixel(_pBody->GetPosition().x),
		MathHelper::ToPixel(_pBody->GetPosition().y)
		);

	_animatedSprite.update(frameTime);

	// Scaling is like a multiplication by -1. So it should only
	// be done once. The following code tries to guarantee that.
	if (_movingForward && _animatedSprite.getScale().x > 0)
		_animatedSprite.scale(-1.f, 1.f);
	else if (!_movingForward && _animatedSprite.getScale().x < 0)
		_animatedSprite.scale(-1.f, 1.f);

	if (playerFound && (_state == Attack))
	{
		if (playerOnRight == 1 && _animatedSprite.getScale() != Vector2f(-1, 1))
		{
			_animatedSprite.setScale(-1, 1);
		}
		else if (playerOnRight == -1 && _animatedSprite.getScale() != Vector2f(1, 1))
		{
			_animatedSprite.setScale(1, 1);
		}
	}

	if (_state == Dead && !_animatedSprite.isPlaying())
	{
		_pBody->GetWorld()->DestroyBody(_pBody);
		_destroyed = true;
	}
}

void Skeleton::Draw(RenderWindow& window, Time dt)
{
	window.draw(_animatedSprite);
}

Skeleton::Skeleton() {}
b2Body* Skeleton::GetPhysicsBody() { return _pBody; }
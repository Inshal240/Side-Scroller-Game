#include "Kirby.h"
using namespace sf;
using namespace std;

void Kirby::changeSprite(State _state)
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
		_animatedSprite.setFrameTime(sf::seconds(0.12f));
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

void Kirby::LoadContent()
{
	_health = *(new Health(50));
	_attackCalled = false;
	_destroyed = false;

	Texture texture;

	// Idle Animation
	texture.loadFromFile("Art\\Kirby\\Idle.png");
	_textureBank.insert(pair<State, Texture>(Idle, texture));

	_animationBank[Idle].setSpriteSheet(_textureBank[Idle]);
	_animationBank[Idle].addFrame(IntRect(0, 0, 25, 37));
	_animationBank[Idle].addFrame(IntRect(0, 0, 25, 37));
	_animationBank[Idle].addFrame(IntRect(0, 0, 25, 37));
	_animationBank[Idle].addFrame(IntRect(50, 0, 25, 37));

	// Walking Animation
	texture.loadFromFile("Art\\Kirby\\Walk.png");
	_textureBank.insert(pair<State, Texture>(Walking, texture));

	_animationBank[Walking].setSpriteSheet(_textureBank[Walking]);
	_animationBank[Walking].addFrame(IntRect(  0, 0,  29 -   0, 38));
	_animationBank[Walking].addFrame(IntRect( 50, 0,  80 -  50, 38));
	_animationBank[Walking].addFrame(IntRect(102, 0, 128 - 102, 38));
	_animationBank[Walking].addFrame(IntRect(154, 0, 176 - 154, 38));

	// Running Animation
	texture.loadFromFile("Art\\Kirby\\Run.png");
	_textureBank.insert(pair<State, Texture>(Running, texture));

	_animationBank[Running].setSpriteSheet(_textureBank[Running]);
	_animationBank[Running].addFrame(IntRect(  0, 0,  29 -   0, 39));
	_animationBank[Running].addFrame(IntRect( 51, 0,  79 -  51, 39));
	_animationBank[Running].addFrame(IntRect(103, 0, 127 - 103, 39));
	_animationBank[Running].addFrame(IntRect(154, 0, 177 - 154, 39));
	_animationBank[Running].addFrame(IntRect(103, 0, 127 - 103, 39));
	_animationBank[Running].addFrame(IntRect(51, 0, 79 - 51, 39));

	// Attack Animation
	texture.loadFromFile("Art\\Kirby\\Attack.png");
	_textureBank.insert(pair<State, Texture>(Attack, texture));

	_animationBank[Attack].setSpriteSheet(_textureBank[Attack]);
	_animationBank[Attack].addFrame(IntRect(  4, 4,  33 -   4, 35 - 4));
	_animationBank[Attack].addFrame(IntRect( 50, 4,  87 -  50, 35 - 4));
	_animationBank[Attack].addFrame(IntRect( 93, 4, 146 -  93, 35 - 4));
	_animationBank[Attack].addFrame(IntRect(152, 6, 193 - 152, 37 - 6));
	_animationBank[Attack].addFrame(IntRect(199, 4, 261 - 199, 39 - 4));
	_animationBank[Attack].addFrame(IntRect(280, 4, 339 - 280, 39 - 4));
	_animationBank[Attack].addFrame(IntRect(351, 1, 388 - 351, 39 - 0));
	_animationBank[Attack].addFrame(IntRect(393, 1, 443 - 393, 39 - 0));
	_animationBank[Attack].addFrame(IntRect(  0, 83 - 34,  39 -   0, 34));
	_animationBank[Attack].addFrame(IntRect(  0, 86 - 34, 39 - 0, 34));
	_animationBank[Attack].addFrame(IntRect(  0, 53, 39 - 0, 87 - 53));

	// Rising
	texture.loadFromFile("Art\\Kirby\\Rising.png");
	_textureBank.insert(pair<State, Texture>(Rising, texture));
	_animationBank[Rising].setSpriteSheet(_textureBank[Rising]);
	_animationBank[Rising].addFrame(IntRect(0, 0, 30, 37));

	// Falling
	texture.loadFromFile("Art\\Kirby\\Falling.png");
	_textureBank.insert(pair<State, Texture>(Falling, texture));
	_animationBank[Falling].setSpriteSheet(_textureBank[Falling]);
	_animationBank[Falling].addFrame(IntRect(0, 0, 27, 39));

	// Hurt Animation
	texture.loadFromFile("Art\\Kirby\\Hurt.png");
	_textureBank.insert(pair<State, Texture>(Hurt, texture));
	_animationBank[Hurt].setSpriteSheet(_textureBank[Hurt]);
	_animationBank[Hurt].addFrame(IntRect(0, 0, 28, 33));
	_animationBank[Hurt].addFrame(IntRect(50, 0, 77 - 50, 33));
	_animationBank[Hurt].addFrame(IntRect(50, 0, 77 - 50, 33));
	_animationBank[Hurt].addFrame(IntRect(50, 0, 77 - 50, 33));
	_animationBank[Hurt].addFrame(IntRect(50, 0, 77 - 50, 33));

	// Death Animation
	texture.loadFromFile("Art\\Kirby\\Hurt.png");
	_textureBank.insert(pair<State, Texture>(Dead, texture));

	_animationBank[Dead].setSpriteSheet(_textureBank[Idle]);
	_animationBank[Dead].addFrame(IntRect(0, 0, 28, 33));
	_animationBank[Dead].addFrame(IntRect(50, 0, 77 - 50, 33));
	_animationBank[Dead].addFrame(IntRect(0, 0, 0, 0));
	_animationBank[Dead].addFrame(IntRect(50, 0, 77 - 50, 33));
	_animationBank[Dead].addFrame(IntRect(0, 0, 0, 0));
	_animationBank[Dead].addFrame(IntRect(50, 0, 77 - 50, 33));
	_animationBank[Dead].addFrame(IntRect(0, 0, 0, 0));
	_animationBank[Dead].addFrame(IntRect(50, 0, 77 - 50, 33));
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

void Kirby::create(Texture& texture, float initX, float initY)
{
	_bodyDef.position.Set(MathHelper::ToUnit(initX), MathHelper::ToUnit(initY));
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.fixedRotation = true;

	_bodyShape.SetAsBox(
		MathHelper::ToUnit(texture.getSize().x / 4),
		MathHelper::ToUnit(texture.getSize().y / 2)
		);

	_animatedSprite.setOrigin(
		texture.getSize().x / 4,
		texture.getSize().y / 2
		);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.3f;
}

void Kirby::handleState()
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

void Kirby::handleEvent(Event gameEvent, Player& player)
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

		if (distanceFromPlayer > 1.2)
		{
			_pBody->SetLinearVelocity(b2Vec2(
				1.2 * playerOnRight,
				_pBody->GetLinearVelocity().y
				));
		}
		// Judge whether to attack or not with a chance of 1/45
		else if (distanceFromPlayer < 1.2)
		{
			int choice = rand() % 45;

			if (choice == 0)
			{
				_attackCalled = true;
			}
		}
	}
}

void Kirby::Update(Event gameEvent, Player& player, Time dt, Time frameTime)
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
	if (_movingForward && _animatedSprite.getScale().x < 0)
		_animatedSprite.scale(-1.f, 1.f);
	else if (!_movingForward && _animatedSprite.getScale().x > 0)
		_animatedSprite.scale(-1.f, 1.f);

	if (playerFound && (_state == Attack))
	{
		if (playerOnRight == 1 && _animatedSprite.getScale() != Vector2f(1, 1))
		{
			_animatedSprite.scale(-1, 1);
		}
		else if (playerOnRight == -1 && _animatedSprite.getScale() != Vector2f(-1, 1))
		{
			_animatedSprite.scale(-1, 1);
		}
	}

	if (_state == Dead && !_animatedSprite.isPlaying())
	{
		_pBody->GetWorld()->DestroyBody(_pBody);
		_destroyed = true;
	}

	float distance = distanceFromBody(player.GetPhysicsBody());
	Player::State playerState = player.GetState();
	int frame = player.GetCurrentFrame();
	int facing = player.GetFacing();

	if (distance < 1.2 && _state == Attack && _animatedSprite.getCurrentFrame() == 5) player.Damage(20); //cout << "Kirby attacking player " << endl ;

	if (distance < 1.3)
	{
		if ((playerOnRight > 0 && facing < 0)
			|| (playerOnRight < 0 && facing > 0))
		{
			DamageByPlayer(playerState, frame);
		}
	}
}

void Kirby::Draw(RenderWindow& window, Time dt)
{
	window.draw(_animatedSprite);
}

Kirby::Kirby() {}
b2Body* Kirby::GetPhysicsBody() { return _pBody; }
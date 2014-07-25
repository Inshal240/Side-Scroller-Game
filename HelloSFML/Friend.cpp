#include "Friend.h"
using namespace sf;
using namespace std;

Friend::Friend()
{
}


Friend::~Friend()
{
}

void Friend::create(Texture& texture, float initX, float initY, int verticalOffset)
{


	_bodyDef.position.Set(MathHelper::ToUnit(initX), MathHelper::ToUnit(initY));
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.fixedRotation = true;

	_bodyShape.SetAsBox(
		MathHelper::ToUnit(texture.getSize().x / 2.f),
		MathHelper::ToUnit(texture.getSize().y / 2.f)
		);

	_cageSprite.setOrigin(
		texture.getSize().x / 2,
		(texture.getSize().y / 2) - 2
		);

	_animatedSprite.setOrigin(
		texture.getSize().x / 6,
		(texture.getSize().y / 2) - verticalOffset
		);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.3f;
}

void Friend::changeSprite(State state)
{
	switch (_state)
	{
	case Freed:
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Freed];
		break;

	case Caged:
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Caged];
		break;

	default:
		break;
	}

	_animatedSprite.play();
}

//void Friend::LoadContent(Texture Caged, Texture Free)
//{
//	_free = false;
//
//	Texture tempTexture;
//	tempTexture.loadFromFile("Art\\Friend\\Jail.png");
//	_textureBank.insert(pair<String, Texture>("jail", tempTexture));
//
//	_textureBank.insert(pair<String, Texture>("free", Free));
//	_textureBank.insert(pair<String, Texture>("caged", Caged));
//
//	_cage.setTexture( _textureBank["jail"] );
//
//	// 
//	_animationBank[Idle].setSpriteSheet(_textureBank[Idle]);
//	_animationBank[Idle].addFrame(IntRect(0, 0, 31 - 0, 53));
//	_animationBank[Idle].addFrame(IntRect(41, 0, 71 - 41, 53));
//	_animationBank[Idle].addFrame(IntRect(85, 0, 115 - 85, 53));
//	_animationBank[Idle].addFrame(IntRect(41, 0, 71 - 41, 53));
//
//	_animatedSprite.setLooped(true);
//	_animatedSprite.play();
//	_animatedSprite.setFrameTime(sf::seconds(0.2f));
//
//	_currentAnimation = &_animationBank["jail"];
//	_animatedSprite.setAnimation(*_currentAnimation);
//
//	create(_textureBank["jail"], 700, 500);
//}

void Friend::handleState()
{
	_previousState = _state;

	if (_free)
	{
		_state = Freed;
	}
}

void Friend::Update(sf::Event gameEvent, Player& player, sf::Time dt, Time frameTime)
{

	handleState();

	if (_state != _previousState)
	{
		changeSprite(_state);
		_animatedSprite.setAnimation(*_currentAnimation);
	}

	_cageSprite.setPosition(
		MathHelper::ToPixel(_pBody->GetPosition().x),
		MathHelper::ToPixel(_pBody->GetPosition().y)
		);

	_animatedSprite.setPosition(
		MathHelper::ToPixel(_pBody->GetPosition().x),
		MathHelper::ToPixel(_pBody->GetPosition().y)
		);

	_animatedSprite.update(frameTime);

	int playerOnRight = player.GetPhysicsBody()->GetPosition().x - _pBody->GetPosition().x;

	if (playerOnRight > 0 && _animatedSprite.getScale().x < 0)
	{
		_animatedSprite.scale(-1.f, 1.f);
	}
	else if (playerOnRight < 0 && _animatedSprite.getScale().x > 0)
	{
		_animatedSprite.scale(-1.f, 1.f);
	}
	
	float d = distanceFromBody( player.GetPhysicsBody() );

	if ( d < 0.5 ) Free();
}

void Friend::Draw(sf::RenderWindow& window, sf::Time dt)
{
	window.draw(_animatedSprite);
	if (!_free) window.draw(_cageSprite);
}

bool Friend::IsFree() const { return _free; }
void Friend::Free() { _free = true; }
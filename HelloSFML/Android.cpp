#include "Android.h"
using namespace sf;
using namespace std;

Android::Android()
{
}


Android::~Android()
{
}

void Android::LoadContent()
{
	_free = false;

	_cageTexture.loadFromFile("Art\\Friend\\Jail.png");
	_cageSprite.setTexture(_cageTexture);

	Texture tempTexture;

	tempTexture.loadFromFile("Art\\Friend\\AndroidCaged.png");
	_textureBank.insert(pair<State, Texture>(Caged, tempTexture));
	tempTexture.loadFromFile("Art\\Friend\\AndroidFree.png");
	_textureBank.insert(pair<State, Texture>(Freed, tempTexture));

	// Caged Animation
	_animationBank[Caged].setSpriteSheet(_textureBank[Caged]);
	_animationBank[Caged].addFrame(IntRect( 59, 0,  99 -  59, 60));
	_animationBank[Caged].addFrame(IntRect(115, 0, 161 - 115, 60));
	_animationBank[Caged].addFrame(IntRect(115, 0, 161 - 115, 60));
	_animationBank[Caged].addFrame(IntRect( 59, 0,  99 -  59, 60));

	// Freed Animation
	_animationBank[Freed].setSpriteSheet(_textureBank[Freed]);
	_animationBank[Freed].addFrame(IntRect(  0, 0,  44 -   0, 64));
	_animationBank[Freed].addFrame(IntRect( 56, 0,  98 -  56, 64));
	_animationBank[Freed].addFrame(IntRect(112, 0, 154 - 112, 64));

	_animatedSprite.setLooped(true);
	_animatedSprite.play();
	_animatedSprite.setFrameTime(sf::seconds(0.2f));

	_animatedSprite.scale(0.8f, 0.8f);

	_currentAnimation = &_animationBank[Caged];
	_animatedSprite.setAnimation(*_currentAnimation);

	create(_cageTexture, 700, 500, 11);
}

#include "Man.h"
using namespace sf;
using namespace std;

Man::Man()
{

}

Man::~Man()
{

}


void Man::LoadContent()
{
	_free = false;

	_cageTexture.loadFromFile("Art\\Friend\\Jail.png");
	_cageSprite.setTexture(_cageTexture);

	Texture tempTexture;

	tempTexture.loadFromFile("Art\\Friend\\ManCaged.png");
	_textureBank.insert(pair<State, Texture>(Caged, tempTexture));
	tempTexture.loadFromFile("Art\\Friend\\ManFree.png");
	_textureBank.insert(pair<State, Texture>(Freed, tempTexture));

	// Caged Animation
	_animationBank[Caged].setSpriteSheet(_textureBank[Caged]);
	_animationBank[Caged].addFrame(IntRect( 0, 0, 31 -  0, 61));
	//_animationBank[Caged].addFrame(IntRect(0, 0, 43 - 0, 41));

	// Freed Animation
	_animationBank[Freed].setSpriteSheet(_textureBank[Freed]);
	_animationBank[Freed].addFrame(IntRect(90, 0, 31, 69));

	_animatedSprite.setLooped(true);
	_animatedSprite.play();
	_animatedSprite.setFrameTime(sf::seconds(0.2f));

	_currentAnimation = &_animationBank[Caged];
	_animatedSprite.setAnimation(*_currentAnimation);

	create(_cageTexture, 700, 500, -2);
}


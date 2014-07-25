#include "Robot.h"
using namespace sf;
using namespace std;

Robot::Robot()
{
}


Robot::~Robot()
{
}

void Robot::LoadContent()
{
	_free = false;
	
	_cageTexture.loadFromFile("Art\\Friend\\Jail.png");
	_cageSprite.setTexture( _cageTexture );
	
	Texture tempTexture;
	
	tempTexture.loadFromFile("Art\\Friend\\RobotCaged.png");
	_textureBank.insert(pair<State, Texture>(Caged, tempTexture));
	tempTexture.loadFromFile("Art\\Friend\\RobotFree.png");
	_textureBank.insert(pair<State, Texture>(Freed, tempTexture));

	// Caged Animation
	_animationBank[Caged].setSpriteSheet(_textureBank[Caged]);
	_animationBank[Caged].addFrame(IntRect(0, 0, 23, 50));
	
	// Freed Animation
	_animationBank[Freed].setSpriteSheet(_textureBank[Freed]);
	_animationBank[Freed].addFrame(IntRect(  0,  0,  40 -   0, 51));
	_animationBank[Freed].addFrame(IntRect( 57,  0,  97 -  57, 51));
	_animationBank[Freed].addFrame(IntRect(108,  0, 148 - 108, 51));
	_animationBank[Freed].addFrame(IntRect(157, -1, 197 - 157, 50));
	_animationBank[Freed].addFrame(IntRect(200,  0, 240 - 200, 51));

	_animatedSprite.setLooped(true);
	_animatedSprite.play();
	_animatedSprite.setFrameTime(sf::seconds(0.2f));
	
	_currentAnimation = &_animationBank[Caged];
	_animatedSprite.setAnimation(*_currentAnimation);
	
	create(_cageTexture, 700, 500, 11);
}
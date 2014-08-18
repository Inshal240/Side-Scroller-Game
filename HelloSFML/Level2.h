#pragma once
#include "state.h"
#include<vector>
#include<map>
#include <iostream>
#include <string>
#include <list>
#include "Ball.h"
#include "Box.h"
#include "Bomb.h"
#include "Wheel.h"
#include "StaticPlatform.h"
#include "JointPlatform.h"
#include "SFMLDebugDraw.h"
#include "SwingSpikeBall.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "EntityType.cpp"
#include "Ranger.h"
#include "Score.h"
#include "Skeleton.h"
#include "TimedSpikes.h"
#include "Robot.h"
#include "Man.h"
#include "Android.h"
#include "Kirby.h"


class Level2 :
	public State
{

private:

	Text HudViewCoins;
	Text HudViewHealth;
	Text HudViewLives;
	sf::RectangleShape HudRect;

	map<std::string, sf::Texture> textureBank;


	vector<Box> boxes;
	vector<StaticPlatform> platforms;
	vector<Bomb> bombs;

	vector<JointPlatform> jointPlatforms;
	vector<Wheel> wheels;
	vector<SwingSpikeBall> spikeChains;
	vector<TimedSpikes> timedSpikes;

	vector<Coin*> coins; //for some (yet unknown) reasons it is not working with object, so I am using pointer-to-object

	Player Edward;
	Ranger enemy;
	Skeleton skeleton;
	Robot robot;
	Kirby kirby;
	Android android;
	Man man;

	Clock frameClock;
	View levelView;
	View hudView;

	int cameraCenter; //for debugging view


	Score *score;

	Font Myfont;
	Font debugFont;
	Text mousePosition;

	//Changes here
	bool EdwardWasAlive;

	Clock GameEndTimer;

public:

	Level2(RenderWindow& window, SFMLDebugDraw& debugDraw, b2World* World, Score* score);
	void LoadContent();

	void HandleInput(Event gameEvent);

	void UnloadContent();

	State::LevelState Update(Event gameEvent, Event prevEvent, Time timeSinceLastUpdateCall);



	void Draw(RenderWindow& window, Time timeSinceLastDrawCall);

	void ResetLevelState();

	void SpreadPickupCoins();

	void SpreadBrickPlatforms();

	void SpreadTrees();

	Level2(void);
	~Level2(void);

	void UnloadLevel();

private:

	void DrawMousePosition();


};



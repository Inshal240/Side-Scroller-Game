#pragma once
#include "State.h"
#include <vector>
#include <iostream>
#include "CollisionListener.h"

using namespace sf;


class menu: public State
{


private:
	enum MenuState
	{
		NewMenu,
		PausedMenu,
		Credit,
		Control,
	};


	
public:

	Texture BackgroundTexture;
	Texture ButtonTexture[5];
	Texture ControlsTexture;
	Texture CreditScreenTexture;

	Sprite Background;
	Sprite Button[5];
	Sprite Controls;
	Sprite Credits;

	menu(RenderWindow& window, SFMLDebugDraw& debugDraw, b2World* World);
	void LoadContent();
	
	void HandleInput(Event gameEvent);

	void UnloadContent();
	 
	State::LevelState Update(Event gameEvent, Event prevEvent, Time timeSinceLastUpdateCall);


	 
	void Draw(RenderWindow& window, Time timeSinceLastDrawCall);



	MenuState MenuIs;

	MenuState MenuWas;

	void SetMenuState(int i);



	~menu(void);
};


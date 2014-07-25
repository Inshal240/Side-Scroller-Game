#pragma once

#include "GameCharacter.h"
#include "Player.h"

class Friend : public GameCharacter
{
protected:
	bool _free;
	
	enum State
	{
		Freed,
		Caged
	};

	State _state;
	State _previousState;

	Sprite _cageSprite;
	Texture _cageTexture;
	std::map<State, Animation> _animationBank;
	std::map<State, Texture> _textureBank;

	void create(Texture& texture, float initX, float initY, int);
	void handleState();
	void changeSprite(State);
	
public:
	//void LoadContent() { };
	//void LoadContent(Texture, Texture);
	void Update(sf::Event gameEvent, Player& player, sf::Time dt, Time frameTime);
	void Draw(sf::RenderWindow& window, sf::Time dt);
	bool IsFree() const;
	void Free();
	Friend();
	~Friend();
};


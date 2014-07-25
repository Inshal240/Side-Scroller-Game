#pragma once
#include "GameCharacter.h"

class Player : public GameCharacter
{
private:
	bool _inAir;
	bool _hit;
	Health _health;
	bool _attack1Called;
	bool _attack2Called;
	bool _attack3Called;
	// Changes here
	b2Vec2 _spawnPoint;

	enum State {
		Idle,
		Walking,
		Running,
		Rising,
		Falling,
		Landing,
		Hurt,
		Dead,
		Attack1,
		Attack2,
		Attack3,
		Special
	};

	State _state;
	State _previousState;

	std::map<State, Animation> _animationBank;
	std::map<State, Texture> _textureBank;
	
	void handleEvent(Event currentEvent, Event oldEvent);
	void handleState();
	void changeSprite(State);
	void create(Texture& texture, float initX, float initY);

public:
	Player();
	Player(Texture& texture, float initX, float initY);

	void SetWorld(b2World& world);

	void LoadContent();
	void Update(sf::Event gameEvent, Event oldGameEvent, sf::Time dt, Time frameTime);

	void Damage(int);

	State GetState();
	b2Body* GetPhysicsBody();

	int GetHealth() { return _health.GetHealth(); }

	// Changes here: removed a function

	Player* IamA( uint16 category ) { _fixtureDef.filter.categoryBits = category; return this; } 

	void ICollideWith( uint16 collisionPartners ) {  _fixtureDef.filter.maskBits = collisionPartners; }

	// Changes here
	void Respawn();
	void SetSpawnPoint(int x, int y);
	b2Vec2 GetSpawnPoint() const;
};

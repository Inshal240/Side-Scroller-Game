#include "Score.h"





Score::Score(RenderWindow& window, SFMLDebugDraw& debugDraw, b2World* World)
	:State(window,debugDraw,World),
	CoinsCollected(0),
	LivesLeft(3),
	totalScore(0)
	
	
{
}


void Score::LoadContent()
{

	//Loading background
	
	Scoreback.loadFromFile("Art\\ScoreBackground.png");
	
	ScoreBackground.setTexture(Scoreback);
	ScoreBackground.setOrigin(450,350);
	ScoreBackground.setPosition(450,350);
	


	//Loading font
	Myfont.loadFromFile("Hudfont.TTF");

	//Seting texts

	CoinsCollectedLabel.setFont(Myfont);
	CoinsCollectedLabel.setCharacterSize(50);
	CoinsCollectedLabel.setPosition(180,100);
	CoinsCollectedLabel.setColor(sf::Color(204,102,0));
	CoinsCollectedLabel.setString(sf::String("COINS COLLECTED:"));

	Coins.setFont(Myfont);
	Coins.setCharacterSize(40);
	Coins.setPosition(440,180);
	Coins.setColor(sf::Color::White);
	Coins.setString(sf::String(std::to_string((long double)CoinsCollected)));

	LivesleftLabel.setFont(Myfont);
	LivesleftLabel.setCharacterSize(50);
	LivesleftLabel.setPosition(260,250);
	LivesleftLabel.setColor(sf::Color(204,102,0));
	LivesleftLabel.setString(sf::String("LIVES LEFT:"));


	Lives.setFont(Myfont);
	Lives.setCharacterSize(40);
	Lives.setPosition(440,330);
	Lives.setColor(sf::Color::White);
	Lives.setString(sf::String(std::to_string((long double)LivesLeft)));

	ScoreMadeLabel.setFont(Myfont);
	ScoreMadeLabel.setCharacterSize(50);
	ScoreMadeLabel.setPosition(240,400);
	ScoreMadeLabel.setColor(sf::Color(204,102,0));
	ScoreMadeLabel.setString(sf::String("TOTAL SCORE:"));


	ScoreMade.setFont(Myfont);
	ScoreMade.setCharacterSize(40);
	ScoreMade.setPosition(390,480);
	ScoreMade.setColor(sf::Color::White);
	ScoreMade.setString(sf::String(std::to_string((long double)(totalScore+(CoinsCollected*400)+(LivesLeft*700)))));
	
	
	

}
	
void Score::HandleInput(Event gameEvent){}

void Score::UnloadContent(){}
	 
State::LevelState Score::Update(Event gameEvent, Event prevEvent, Time timeSinceLastUpdateCall)
{
	
	

	return LState;
}


void Score::Draw(RenderWindow& window, Time timeSinceLastDrawCall)
{
	window.setFramerateLimit(70);
	window.clear();
	window.draw(ScoreBackground);
	window.draw(CoinsCollectedLabel);
	window.draw(Coins);
	window.draw(Lives);
	window.draw(LivesleftLabel);
	window.draw(ScoreMade);
	window.draw(ScoreMadeLabel);
	window.display();

}


void Score::IncrementScore(int x)
{
	totalScore+=x;
}
void Score::IncrementCoins()
{
	CoinsCollected++;
}
void Score::IncrementLife()
{
	LivesLeft++;
}

void Score::DecrementScore(int x)
{
	totalScore-=x;
}
void Score::DecrementCoins()
{
	CoinsCollected--;
}
void Score::DecrementLife()
{
	LivesLeft--;
}


int Score::GetLives()
{
	return LivesLeft;
}
int Score::GetScore()
{
	return totalScore;
}
int Score::GetCoins()
{
	return CoinsCollected;
}
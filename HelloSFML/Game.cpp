#include "Game.h"

// @see : http://stackoverflow.com/questions/10647448/why-constant-data-member-of-a-class-need-to-be-initialized-at-the-constructor
Game::Game(RenderWindow& window, SFMLDebugDraw& debugDraw) 
	: timeStep( 1.0f / 60.0f ),
	 _rWindow(window), 
	 _rSfmlDebugDraw(debugDraw),
	 gameEventListener()
{
	stateName=Menu;
	_pMenu=new menu(_rWindow,_rSfmlDebugDraw,_pWorld);
	_pcurLevel=NULL;
	
}

bool Game::Run()
{
	
	SplashScreen();

	LoadScreen();
	

	Initialize();
	_currentState=_pMenu;
	//_currentState = new Level1(_rWindow,_rSfmlDebugDraw,_pWorld,score);
	
	LoadContent();

	Clock timeElapsed;

	while ( _rWindow.isOpen() )
	{
		
		_rWindow.pollEvent(e);

		if ( e.type == Event::Closed )
		{
			_rWindow.close();
			UnloadContent();
			break;
		}

		if(e.type==Event::KeyPressed)
		{
			if(Keyboard::isKeyPressed(Keyboard::LAlt) && Keyboard::isKeyPressed(Keyboard::F4))
			{
				_rWindow.close();
				UnloadContent();
				break;
			}

			
		}
		
		HandleInput( e );

		//Time lastUpdateCall = timeElapsed.restart();

		if ( timeElapsed.getElapsedTime().asMilliseconds() >= timeStep)
		{
			Update( e, oldEvent, timeElapsed.restart() );
		}
	
		Time lastDrawCall = /*lastUpdateCall +*/ timeElapsed.getElapsedTime(); //.restart();

		Draw( _rWindow, lastDrawCall );

		oldEvent = e;
	}
	
	return true;
}



void Game::Initialize() 
{
	
	
	
	_pWorld = new b2World( b2Vec2(0, 10.f) );
	_pWorld->SetAllowSleeping( true );
	_pWorld->SetDebugDraw( &_rSfmlDebugDraw );
	_pWorld->SetContactListener( &gameEventListener );
}


void Game::LoadContent() 
{	

_currentState->LoadContent();


}

void Game::UnloadContent() 
{
	delete _pWorld;
	//_currentState->UnloadContent();
	if(_pcurLevel!=NULL)
		delete _pcurLevel;

	
	//delete _currentState;
	
}

void Game::Update(Event gameEvent, Event previousGameEvent, Time timeSinceLastUpdateCall ) 
{

	State::LevelState st=_currentState->Update(gameEvent,previousGameEvent,timeSinceLastUpdateCall);
	HandleState(st);

}

void Game::Draw(RenderWindow& window, Time timeSinceLastDrawCall ) 
{
	_currentState->Draw(window,timeSinceLastDrawCall);
	

}

void Game::HandleInput(Event gameEvent)
{
	_currentState->HandleInput(gameEvent);
	
}



void Game::SplashScreen()
{
	Clock ElapsedTime;
	ElapsedTime.restart();
	Texture Splash;
	Splash.loadFromFile("Art\\SplashScreen.png");
	_rWindow.clear();
	Splash.setSmooth(true);
	
	Sprite Screen;
	Screen.setTexture(Splash);
	
	
	
	Screen.scale(_rWindow.getSize().x/(float)Splash.getSize().x,_rWindow.getSize().y/(float)Splash.getSize().y);

	_rWindow.draw(Screen);
	_rWindow.display();
	while(ElapsedTime.getElapsedTime().asSeconds()<4.f) //show splash screen for 4 seconds
	{
		_rWindow.pollEvent(e);

		if ( e.type == Event::Closed )
		{
			_rWindow.close();
			exit(0);
		}
		if(e.type==Event::KeyPressed)
		{
			if(Keyboard::isKeyPressed(Keyboard::LAlt) && Keyboard::isKeyPressed(Keyboard::F4))
			{
				_rWindow.close();
				
				exit(0);
			}
		}
		
	}
	ElapsedTime.restart();
	while(ElapsedTime.getElapsedTime().asSeconds()<1.5f)
	{
		_rWindow.pollEvent(e);

		if ( e.type == Event::Closed )
		{
			_rWindow.close();
			exit(0);
		}
		if(e.type==Event::KeyPressed)
		{
			if(Keyboard::isKeyPressed(Keyboard::LAlt) && Keyboard::isKeyPressed(Keyboard::F4))
			{
				_rWindow.close();
				exit(0);
				
			}
		}
		
		_rWindow.clear();
		Screen.setColor(sf::Color(Screen.getColor().r,Screen.getColor().g,Screen.getColor().b,Screen.getColor().a/2 + 0.58));
		_rWindow.draw(Screen);
		_rWindow.display();
	}
}




void Game::LoadScreen()
{
	Texture loading[4];

	loading[0].loadFromFile("Art\\Loading4.png");
	loading[1].loadFromFile("Art\\Loading3.png");
	loading[2].loadFromFile("Art\\Loading2.png");
	loading[3].loadFromFile("Art\\Loading1.png");
	Clock TimeElapsed;

	Sprite Screen;
	Screen.scale(_rWindow.getSize().x/(float)loading[0].getSize().x,_rWindow.getSize().y/(float)loading[0].getSize().y);
	TimeElapsed.restart();
	

	while(TimeElapsed.getElapsedTime().asSeconds()<2.0f)
	{
		
		Clock interval;
		for(int i=0;i<4;i++)
		{
			interval.restart();
			_rWindow.clear();
			Screen.setTexture(loading[i]);
			_rWindow.draw(Screen);
			_rWindow.display();
			while(interval.getElapsedTime().asMilliseconds()<800);
			

		}
	}

}



void Game::HandleState(State::LevelState lState)
{
	if(lState==State::Complete)
	{
		if(stateName==GameState::ScoreBoard)//ScoreBoard will always return completed
		{
			stateName=GameState::Menu;
			if(_pcurLevel!=NULL)
			{
				_pcurLevel->UnloadContent();
				delete _pcurLevel;
			}
			_pcurLevel=NULL;
		}
		else if(stateName==Menu)//Menu will return completed when new game is selected
		{
			if(_pcurLevel!=NULL)
			{
				_pcurLevel->UnloadContent();
				delete _pcurLevel;
			}
			_pcurLevel=NULL;
			score=new Score(_rWindow,_rSfmlDebugDraw,_pWorld); // Initializing new score
			stateName=(GameState)(stateName+1);
		}
		else 
		{
			stateName=(GameState)(stateName+1);
			if(_currentState==(State*)_pcurLevel)
				_pcurLevel=NULL;
			_currentState->UnloadContent();
			
			delete _currentState;
		}
		

		switch(stateName)
		{
		case(Menu):
			
			_currentState=_pMenu;
			_pMenu->SetMenuState(1); // Argument(1) For New Menu ...   
			break;
			
		case(Level_1):
			LoadScreen();
			_currentState=new Level1(_rWindow,_rSfmlDebugDraw,_pWorld,score);
			_currentState->LoadContent();
			break;

		case(Level_2) :
			_currentState = new Level2(_rWindow, _rSfmlDebugDraw, _pWorld, score);
			_currentState->LoadContent();
			break;

		case(ScoreBoard):
			_currentState=score;
			_currentState->LoadContent();
			break;
		}


		
	}

	else if(lState==State::Paused)
	{
		if(stateName==GameState::Level_1)
		{
			LevelNo=Level_1;
			_pcurLevel=_currentState;
			stateName=GameState::Menu;
			_currentState=_pMenu;
			_pMenu->SetMenuState(0);// Paused Menu
			_pcurLevel->ResetLevelState();
			
		}


		if (stateName == GameState::Level_2)
		{
			LevelNo = Level_2;
			_pcurLevel = _currentState;
			stateName = GameState::Menu;
			_currentState = _pMenu;
			_pMenu->SetMenuState(0);// Paused Menu
			_pcurLevel->ResetLevelState();

		}
	}
	else if(lState==State::Playing)
	{

		if(stateName==Menu)
		{
			stateName=LevelNo;
			_currentState=_pcurLevel;


		}
	}

	else if(lState==State::Lost)
	{
		if(stateName==GameState::Menu)//Menu will return lost when Exit is pressed
		{
			stateName=GameState::Exit;
			ExitScreen();
			
		}
		else
		{
			
			stateName=GameState::ScoreBoard;
			_currentState=score;
			_currentState->LoadContent();
		}

	}
	

}


void Game::ExitScreen()
{
	//Exit Screen coding

	_rWindow.close();
	UnloadContent();
	
	exit(0);

}
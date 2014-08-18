#include "menu.h"



menu::~menu(void)
{
}


menu::menu(RenderWindow& window, SFMLDebugDraw& debugDraw, b2World* World)
	:State(window,debugDraw,World)
{
	
	MenuIs=NewMenu;
	MenuWas=NewMenu;
	LState=Paused;
	
}


void menu::LoadContent()
{
	
	BackgroundTexture.loadFromFile("Art\\MenuBackground.png");

	ButtonTexture[0].loadFromFile("Art\\NEWGAME.png");
	ButtonTexture[1].loadFromFile("Art\\CONTINUE.png");
	ButtonTexture[2].loadFromFile("Art\\OPTIONS.png");
	ButtonTexture[3].loadFromFile("Art\\CREDITS.png");
	ButtonTexture[4].loadFromFile("Art\\QUIT.png");

	ControlsTexture.loadFromFile("Art\\Controls.png");
	CreditScreenTexture.loadFromFile("Art\\Creditscreen.png");



	Background.setTexture(BackgroundTexture);
	
	Background.setPosition(0,0);
	Background.setOrigin(0,0);


	
	Button[0].setTexture(ButtonTexture[0]);
	Button[0].setPosition(0,0);
	Button[0].setOrigin(0,0);

	Button[1].setTexture(ButtonTexture[1]);
	Button[1].setPosition(0,0);
	Button[1].setOrigin(0,0);

	Button[2].setTexture(ButtonTexture[2]);
	Button[2].setPosition(0,0);
	Button[2].setOrigin(0,0);

	Button[3].setTexture(ButtonTexture[3]);
	Button[3].setPosition(0,0);
	Button[3].setOrigin(0,0);

	Button[4].setTexture(ButtonTexture[4]);
	Button[4].setPosition(0,0);
	Button[4].setOrigin(0,0);


	Controls.setTexture(ControlsTexture);
	Controls.setPosition(0,0);
	Controls.setOrigin(0,0);

	Credits.setTexture(CreditScreenTexture);
	Credits.setPosition(0,0);
	Credits.setOrigin(0,0);



}

void menu::HandleInput(Event gameEvent)
{
	/*LState = Complete;
	return;
	*/
	//there is some bug with menu.
	// it cause ExitMenu() to be called immidiately after showing menu screen
	Vector2i pos=Mouse::getPosition(_rWindow);
	switch(MenuIs)
	{
	case NewMenu:
	
		
		
		if(gameEvent.type==Event::MouseButtonPressed)
		{
			
			cout<<pos.x<<","<<pos.y<<endl;
			if ((pos.x>655) && (pos.x < 930) && (pos.y > 200) && (pos.y <260))
			{
				

				LState=Complete;
				//Button[0].setColor(sf::Color(Button[0].getColor().r,Button[0].getColor().g,Button[0].getColor().b,200));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 300) && (pos.y <360))
			{
				//Button[1].setColor(sf::Color(Button[1].getColor().r,Button[1].getColor().g,Button[1].getColor().b,200));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 400) && (pos.y <465))
			{
				MenuIs=Control;
				//Button[2].setColor(sf::Color(Button[1].getColor().r,Button[1].getColor().g,Button[1].getColor().b,200));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 500) && (pos.y <575))
			{
				MenuIs=Credit;
				//Button[3].setColor(sf::Color(Button[3].getColor().r,Button[3].getColor().g,Button[0].getColor().b,200));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 610) && (pos.y <670))
			{
				LState=Lost;
				//Button[4].setColor(sf::Color(Button[4].getColor().r,Button[4].getColor().g,Button[4].getColor().b,200));
			}
			
		
		}


		if(gameEvent.type=Event::MouseButtonReleased)
		{
			if((pos.x>655) && (pos.x < 930) && (pos.y > 200) && (pos.y <260) )
			{
				for(int i=0;i<5;i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r,Button[i].getColor().g,Button[i].getColor().b,255));
				}
				
				Button[0].setColor(sf::Color(Button[0].getColor().r,Button[0].getColor().g,Button[0].getColor().b,180));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 300) && (pos.y <360))
			{
				for(int i=0;i<5;i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r,Button[i].getColor().g,Button[i].getColor().b,255));
				}

				Button[1].setColor(sf::Color(Button[1].getColor().r,Button[1].getColor().g,Button[1].getColor().b,255));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 400) && (pos.y <465))
			{
				for(int i=0;i<5;i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r,Button[i].getColor().g,Button[i].getColor().b,255));
				}
				
				Button[2].setColor(sf::Color(Button[2].getColor().r,Button[1].getColor().g,Button[1].getColor().b,180));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 500) && (pos.y <575))
			{
				for(int i=0;i<5;i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r,Button[i].getColor().g,Button[i].getColor().b,255));
				}

				Button[3].setColor(sf::Color(Button[3].getColor().r,Button[3].getColor().g,Button[0].getColor().b,180));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 610) && (pos.y <670))
			{
				
				for(int i=0;i<5;i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r,Button[i].getColor().g,Button[i].getColor().b,255));
				}
				Button[4].setColor(sf::Color(Button[4].getColor().r,Button[4].getColor().g,Button[4].getColor().b,180));
			}
			else
				for(int i=0;i<5;i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r,Button[i].getColor().g,Button[i].getColor().b,255));
				}
			 
				
		}

		break;
	case PausedMenu:



		if (gameEvent.type == Event::MouseButtonPressed)
		{

			cout << pos.x << "," << pos.y << endl;
			if ((pos.x>655) && (pos.x < 930) && (pos.y > 200) && (pos.y <260))
			{


				LState = Complete;
				//Button[0].setColor(sf::Color(Button[0].getColor().r,Button[0].getColor().g,Button[0].getColor().b,200));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 300) && (pos.y <360))
			{
				LState = Playing;
				//Button[1].setColor(sf::Color(Button[1].getColor().r,Button[1].getColor().g,Button[1].getColor().b,200));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 400) && (pos.y <465))
			{
				MenuIs = Control;
				//Button[2].setColor(sf::Color(Button[1].getColor().r,Button[1].getColor().g,Button[1].getColor().b,200));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 500) && (pos.y <575))
			{
				MenuIs = Credit;
				//Button[3].setColor(sf::Color(Button[3].getColor().r,Button[3].getColor().g,Button[0].getColor().b,200));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 610) && (pos.y <670))
			{
				LState = Lost;
				//Button[4].setColor(sf::Color(Button[4].getColor().r,Button[4].getColor().g,Button[4].getColor().b,200));
			}


		}


		if (gameEvent.type = Event::MouseButtonReleased)
		{
			if ((pos.x>655) && (pos.x < 930) && (pos.y > 200) && (pos.y <260))
			{
				for (int i = 0; i<5; i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r, Button[i].getColor().g, Button[i].getColor().b, 255));
				}

				Button[0].setColor(sf::Color(Button[0].getColor().r, Button[0].getColor().g, Button[0].getColor().b, 180));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 300) && (pos.y <360))
			{
				for (int i = 0; i<5; i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r, Button[i].getColor().g, Button[i].getColor().b, 255));
				}

				Button[1].setColor(sf::Color(Button[1].getColor().r, Button[1].getColor().g, Button[1].getColor().b, 180));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 400) && (pos.y <465))
			{
				for (int i = 0; i<5; i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r, Button[i].getColor().g, Button[i].getColor().b, 255));
				}

				Button[2].setColor(sf::Color(Button[2].getColor().r, Button[1].getColor().g, Button[1].getColor().b, 180));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 500) && (pos.y <575))
			{
				for (int i = 0; i<5; i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r, Button[i].getColor().g, Button[i].getColor().b, 255));
				}

				Button[3].setColor(sf::Color(Button[3].getColor().r, Button[3].getColor().g, Button[0].getColor().b, 180));
			}
			else if ((pos.x>655) && (pos.x < 930) && (pos.y > 610) && (pos.y <670))
			{

				for (int i = 0; i<5; i++)
				{
					Button[i].setColor(sf::Color(Button[i].getColor().r, Button[i].getColor().g, Button[i].getColor().b, 255));
				}
				Button[4].setColor(sf::Color(Button[4].getColor().r, Button[4].getColor().g, Button[4].getColor().b, 180));
			}
			else
				for (int i = 0; i<5; i++)
				{
				Button[i].setColor(sf::Color(Button[i].getColor().r, Button[i].getColor().g, Button[i].getColor().b, 255));
				}


		}


	case Credit:
		if(gameEvent.type=Event::KeyPressed)
		{
			if(Keyboard::isKeyPressed(Keyboard::Return))
				MenuIs=MenuWas;
		}
		
		break;
	case Control:
		if(gameEvent.type=Event::KeyPressed)
		{
			if(Keyboard::isKeyPressed(Keyboard::Return))
				MenuIs=MenuWas;
		}
		break;


	}



	



}

void menu::UnloadContent()
{
}

State::LevelState menu::Update(Event gameEvent, Event prevEvent, Time timeSinceLastUpdateCall)
{
	
	

	return LState;
}

void menu::Draw(RenderWindow& window, Time timeSinceLastDrawCall)
{
	
	window.setView(window.getDefaultView());
	window.clear();
	switch(MenuIs)
	{
	case NewMenu:
		_rWindow.draw(Background);
		for(int i=0;i<5;i++)
		{
			_rWindow.draw(Button[i]);
		}
		break;
	case Credit:
		_rWindow.draw(Credits);
		break;
	case Control:
		_rWindow.draw(Controls);
		break;
	case PausedMenu:
		_rWindow.draw(Background);
		for(int i=0;i<5;i++)
		{
			_rWindow.draw(Button[i]);
		}
		break;
	

	}
	_rWindow.display();
}

void menu::SetMenuState(int i)
{
	if(i==0)
	{
		MenuIs=MenuWas=PausedMenu;
	}
	else
	{
		MenuIs=MenuWas=NewMenu;
	}
	LState=Paused;
}
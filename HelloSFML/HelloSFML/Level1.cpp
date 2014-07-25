#include "Level1.h"


Level1::Level1(RenderWindow& window, SFMLDebugDraw& debugDraw, b2World* World,Score* score)
	:State(window,debugDraw,World),
	 levelView(window.getView()),
	 hudView(),
	 score(score)
{

	hudView.reset(FloatRect(0,0,900,700));
	hudView.setViewport(FloatRect(0,0,1,1)); // target rect - in ratio

	cameraCenter = levelView.getCenter().x;	  //_rWindow = window;
}

Level1::~Level1(void)
{
}

void Level1::LoadContent()
{


	Myfont.loadFromFile("Hudfont.TTF");

	debugFont.loadFromFile("consola.ttf");

	Texture skull;
	skull.loadFromFile("Art\\Skull.png");
	textureBank.insert( pair<string, Texture>("skull", skull) );

	Texture rotatoryBlade1;
	rotatoryBlade1.loadFromFile("Art\\SawBig.png");
	textureBank.insert( pair<string, Texture>("blade1", rotatoryBlade1) );

	
	Texture rotatoryBlade2;
	rotatoryBlade2.loadFromFile("Art\\SawSmall.png");
	textureBank.insert( pair<string, Texture>("blade2", rotatoryBlade2) );

	Texture ground;
	ground.loadFromFile("Art\\GroundBrownExtended.png");
	textureBank.insert( pair<string, Texture>("brownGround", ground) );

	Texture woodSpikes;
	woodSpikes.loadFromFile("Art\\WoodspikeUp2.png");
	textureBank.insert( pair<string, Texture>("woodSpikes", woodSpikes) );

	Texture woodSpikes2;
	woodSpikes2.loadFromFile("Art\\TwoSpikesWood.png");
	textureBank.insert( pair<string, Texture>("twospikes", woodSpikes2) );

	Texture grassGround;
	grassGround.loadFromFile("Art\\GrassGroundExtended.png");
	textureBank.insert( pair<string, Texture>("grassGround", grassGround) );

	Texture boundaryWall;
	boundaryWall.loadFromFile("Art\\BoundaryWall.png");
	textureBank.insert( pair<string, Texture>("boundaryWall", boundaryWall) );

	Texture grayStone;
	grayStone.loadFromFile("Art\\PlatformStone.png");
	grayStone.setRepeated(true);
	textureBank.insert( pair<string, Texture>("grayStone", grayStone) );

	Texture treeTexture;
	treeTexture.loadFromFile("Art\\Tree.png");
	treeTexture.setRepeated(true); //if we want to have a 'bunch' of trees
	textureBank.insert( pair<string, Texture>("treeTexture", treeTexture) );

	Texture brickStone;
	brickStone.loadFromFile("Art\\BrickSmall.png");
	brickStone.setRepeated(true);
	textureBank.insert( pair<string, Texture>("brickStone", brickStone) );

	//textures for spike ball chains
	Texture chainTexture;
	chainTexture.loadFromFile("Art\\ChainLinkShortGrey.png");
	textureBank.insert( pair<string, Texture>("chainLink", chainTexture) );

	Texture spikeyBallTexture;
	spikeyBallTexture.loadFromFile("Art\\SpikeBallResized.png");
	textureBank.insert( pair<string, Texture>("spikeyBall", spikeyBallTexture) );

	Texture coinTexture;
	coinTexture.loadFromFile("Art\\coin.png");
	textureBank.insert( pair<string, Texture>("coin", coinTexture) );

	Texture SideWalls;
	SideWalls.loadFromFile("Art\\Wall.png");
	textureBank.insert(pair<string,Texture>("wall",SideWalls));


	/******************************************************
	* End loading textures , start initializing game objects
	*******************************************************/

	HudViewCoins.setFont(Myfont);
	HudViewCoins.setCharacterSize(20);
	HudViewCoins.setPosition(580,5);
	HudViewCoins.setColor(sf::Color::White);

	HudViewHealth.setFont(Myfont);
	HudViewHealth.setCharacterSize(20);
	HudViewHealth.setPosition(580,35);
	HudViewHealth.setColor(sf::Color::White);


	HudRect.setFillColor(Color(256,256,256,200));
	HudRect.setSize(Vector2f(350,70));
	HudRect.setPosition(555,0);
	HudRect.setOrigin(0,0);

	//mousePosition.setFont( Myfont );
	//mousePosition.setCharacterSize( 12 );
	//mousePosition.setPosition( 0,0);
	//mousePosition.setColor( Color::Blue );


	//Ball ball(textureBank["skull"], 200, 40+7 );
	//ball.SetWorld(*_pWorld);
	//balls.push_back( ball ); //shown in hud

	SpreadPickupCoins();

	SpreadBrickPlatforms();

	SpreadTrees(); //Oh yes! we LOVE nature.



	//Boundary walls

	StaticPlatform Wall1(textureBank["wall"],0,350,100.0f,0);
	Wall1.SetWorld(*_pWorld);
	platforms.push_back(Wall1);

	StaticPlatform Wall2(textureBank["wall"],2300,350,100.0f,0);
	Wall2.SetWorld(*_pWorld);
	platforms.push_back(Wall2);





	//end wall



	//load the (cruel) spikey ball


	SwingSpikeBall spikeChain(textureBank["chainLink"], textureBank["spikeyBall"], 400, 160, 0);
	spikeChain.IamA( SPIKE_BALL )->ICollideWith( EDWARD );
	spikeChain.SetWorld( *_pWorld );
	spikeChains.push_back(spikeChain);

	SwingSpikeBall spikeChain2(textureBank["chainLink"], textureBank["spikeyBall"], 1250, 260, 0);
	spikeChain2.IamA( SPIKE_BALL )->ICollideWith( EDWARD );
	spikeChain2.SetWorld( *_pWorld );
	spikeChains.push_back(spikeChain2);

	TimedSpikes timed( textureBank["twospikes"], 150, 270 , (int)2);
	timed.SetWorld(*_pWorld);
	timedSpikes.push_back( timed );

	//start first gray ladder
	//origin of next level = origin of lower level + 24 (only x coord)
	StaticPlatform platform( textureBank["grayStone"], 200, 700-48-48-48, (int)4);
	platform.SetWorld( *_pWorld );
	platforms.push_back( platform );

	StaticPlatform l2( textureBank["grayStone"], 200+24, 700-48-48-48-48, (int)3);
	l2.SetWorld( *_pWorld );
	platforms.push_back( l2 );

	StaticPlatform l3( textureBank["grayStone"], 200+24+24, 700-48-48-48-48-48, (int)2);
	l3.SetWorld( *_pWorld );
	platforms.push_back( l3 );

	//end gray ladder

	StaticPlatform spike( textureBank["twospikes"], 250, 100, 400.0f, 0.0f);
	spike.SetWorld( *_pWorld );
	spike.IamA(EntityType::SPIKE)->ICollideWith(EntityType::EDWARD|EntityType::ENEMIES);
	platforms.push_back( spike );



	StaticPlatform spike1( textureBank["woodSpikes"], 1000, 700-48-48-40);
	spike1.IamA(SPIKE)->ICollideWith(EDWARD|ENEMIES);
	spike1.SetWorld( *_pWorld );
	platforms.push_back( spike1 );

	StaticPlatform spike2( textureBank["twospikes"], 390, 700-25);//Under ground spikes
	spike2.IamA(SPIKE)->ICollideWith(EDWARD|ENEMIES);
	spike2.SetWorld( *_pWorld );
	platforms.push_back( spike2 );

	StaticPlatform spike3( textureBank["woodSpikes"], 630, 700-48-48-40);
	spike3.IamA(SPIKE)->ICollideWith(EDWARD|ENEMIES);
	spike3.SetWorld( *_pWorld );
	platforms.push_back( spike3 );

	JointPlatform b1( textureBank["blade2"], 150, 200 , true );
	b1.SetWorld(*_pWorld);
	jointPlatforms.push_back( b1 );

	
	JointPlatform b2( textureBank["blade2"], 1150, 300 , true );
	b2.SetWorld(*_pWorld);
	jointPlatforms.push_back( b2 );

	//JointPlatform b2( textureBank["blade2"], 120, 200 , true );
	//b2.SetWorld(*_pWorld);
	//JointPlatforms.push_back( b2 );

	//start second gray ladder
	//origin of next level = origin of lower level + 24 (only x coord)
	StaticPlatform ladder1( textureBank["grayStone"], 1075 + 200, 700-48-48-48, (int)5);
	ladder1.SetWorld( *_pWorld );
	platforms.push_back( ladder1 );

	StaticPlatform ladder2( textureBank["grayStone"], 1075 + 200, 700-48-48-48-48, (int)3);
	ladder2.SetWorld( *_pWorld );
	platforms.push_back( ladder2 );

	StaticPlatform ladder3( textureBank["grayStone"], 1075 + 200, 700-48-48-48-48-48, (int)1,0.35f);
	ladder3.SetWorld( *_pWorld );
	platforms.push_back( ladder3 );

	//end 2nd gray ladder

	//start gray wall

	StaticPlatform wall1( textureBank["grayStone"], 800, 24, (int)4);
	wall1.SetWorld( *_pWorld );
	platforms.push_back( wall1 );

	StaticPlatform wall2( textureBank["grayStone"], 800, 48+24, (int)4);
	wall2.SetWorld( *_pWorld );
	platforms.push_back( wall2 );

	StaticPlatform wall3( textureBank["grayStone"], 800, 96+24, (int)4);
	wall3.SetWorld( *_pWorld );
	platforms.push_back( wall3 );

	//end gray wall

	//start grassy ground

	StaticPlatform grassCover1( textureBank["grassGround"], 125, 700-48-48, 450.0f, 0);
	grassCover1.SetWorld( *_pWorld );
	platforms.push_back( grassCover1 );

	StaticPlatform grassCover2( textureBank["grassGround"], 600, 700-48-48, 350.0f, 0);
	grassCover2.SetWorld( *_pWorld );
	platforms.push_back( grassCover2 );

	StaticPlatform grassCover3( textureBank["grassGround"], 1100, 700-48-48);
	grassCover3.SetWorld( *_pWorld );
	platforms.push_back( grassCover3 );

	StaticPlatform grassCover4( textureBank["grassGround"], 1900, 700-48-48);
	grassCover4.SetWorld( *_pWorld );
	platforms.push_back( grassCover4 );



	//load ground

	StaticPlatform ground1( textureBank["brownGround"], 125, 700-48, 450.0f, 0); //width 250
	ground1.SetWorld( *_pWorld );
	platforms.push_back( ground1 );

	StaticPlatform ground3( textureBank["brownGround"], 600, 700-48, 350.0f, 0);
	ground3.SetWorld( *_pWorld );
	platforms.push_back( ground3 );

	//continued ground
	StaticPlatform ground2( textureBank["brownGround"], 1100, 700-48);
	ground2.SetWorld( *_pWorld );
	platforms.push_back( ground2 );

	StaticPlatform ground4( textureBank["brownGround"], 1900, 700-48);
	ground4.SetWorld( *_pWorld );
	platforms.push_back( ground4);


	//load characters
	Edward.LoadContent();
	Edward.IamA( EDWARD )->ICollideWith( HARMFUL_OBSTACLES | HARMFUL_OBSTACLES );
	Edward.SetWorld(*_pWorld);
	// Changes here
	Edward.SetSpawnPoint(100, 500);
	Edward.Respawn();

	//load enemy
	enemy.LoadContent();
	enemy.IamA( RANGER )->ICollideWith(  HARMLESS_OBSTACLES );
	enemy.SetWorld(*_pWorld);
	enemy.MoveTo(900, 500);

	skeleton.LoadContent();
	skeleton.IamA( SKELETON )->ICollideWith( HARMLESS_OBSTACLES );
	skeleton.SetWorld(*_pWorld);


}

void Level1::UnloadContent()
{
	for ( int i = 0; i < coins.size(); ++i)
	{
		delete coins[i];
	}
}

State::LevelState Level1::Update(Event gameEvent, Event previousGameEvent, Time timeSinceLastUpdateCall )
{
	//_miniView.move(1,0);

	//for debugging
	

	Time frameTime = frameClock.restart();

	//handles camera movement
		//-- keep edward at center of screen

	if( MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().x) > _rWindow.getSize().x/2)
	{
		levelView.setCenter(sf::Vector2f(MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().x),levelView.getCenter().y));

		if( MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().x) > (2300-_rWindow.getSize().x/2))
		levelView.setCenter(sf::Vector2f(2300-_rWindow.getSize().x/2.f,_rWindow.getSize().y/2.f));
	}
	else
		levelView.setCenter(sf::Vector2f(_rWindow.getSize().x/2.f,_rWindow.getSize().y/2.f));



		//levelView.setCenter(sf::Vector2f(
		//	//MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().x),
		//	cameraCenter,
		//	levelView.getCenter().y
		//));

	//end camera movement
	//if(MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().y)>750)
	//	Edward.Respawn(_pWorld,100,300);

	_pWorld->Step( timeStep, 8, 8);

	for ( int i = 0; i < platforms.size(); ++i)
		platforms[i].Update(gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < spikeChains.size(); ++i)
		spikeChains[i].Update( gameEvent, timeSinceLastUpdateCall );


	for ( int i = 0; i < coins.size(); ++i)
		coins[i]->Update( gameEvent, timeSinceLastUpdateCall );

	
	for ( int i = 0; i < jointPlatforms.size(); ++i)
		jointPlatforms[i].Update( gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < timedSpikes.size(); ++i)
		timedSpikes[i].Update( gameEvent, timeSinceLastUpdateCall );

	//pc2.Update( gameEvent, timeSinceLastUpdateCall );


	Edward.Update(gameEvent, previousGameEvent, timeSinceLastUpdateCall, frameTime);
	
	// Changes here
	if ( !enemy.IsDestroyed() ) 
		enemy.Update(gameEvent, Edward, timeSinceLastUpdateCall, frameTime);


	skeleton.Update(gameEvent, Edward, timeSinceLastUpdateCall, frameTime );

	sf::String Coinscount="COINS COLLECTED: "+to_string((long double)score->GetCoins());
	
	Vector2i p = Mouse::getPosition( _rWindow );

	sf::String mouseString = " ( " +  to_string((long double)p.x ) +  " , "  + to_string((long double) p.y) + " ) ";

	HudViewCoins.setString(mouseString);

	//mousePosition.setString( mouseString );

	sf::String curhealth ="HEALTH: "+to_string((long double)Edward.GetHealth())+"%";

	HudViewHealth.setString(curhealth);

	for ( int i = 0; i < coins.size(); ++i)
		if(coins[i]->isCollected)
		{
			_pWorld->DestroyBody(coins[i]->GetPhysicsBody());
			Coin * temp=coins[i];
			coins.erase(coins.begin()+i);
			delete temp;
			score->IncrementCoins();
			cout<<"Coins collected: "<<score->GetCoins()<<endl;
		}



	return LState;


}

void Level1::Draw(RenderWindow& window, Time timeSinceLastDrawCall )
{
	_rWindow.clear( Color(255,255,255) );
	
	_rWindow.setView( levelView );

//	DrawMousePosition();

	//Vector2i p = Mouse::getPosition(_rWindow);

	//String pos = "( " + to_string((long double)p.x) +  " , " + to_string((long double)p.y) + " ) ";



	//_rWindow.draw(testSprite);

	// _rWindow.clear( Color::Red );

	for ( int i = 0; i < platforms.size(); ++i)
		platforms[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < spikeChains.size(); ++i)
		spikeChains[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < coins.size(); ++i)
		coins[i]->Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < jointPlatforms.size(); ++i)
		jointPlatforms[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < timedSpikes.size(); ++i)
		timedSpikes[i].Draw( _rWindow, timeSinceLastDrawCall );

	//pc2.Draw(_rWindow, timeSinceLastDrawCall );

	if ( !enemy.IsDestroyed() ) enemy.Draw(_rWindow, timeSinceLastDrawCall);


	skeleton.Draw( _rWindow, timeSinceLastDrawCall );

	Edward.Draw(_rWindow, timeSinceLastDrawCall);

	_pWorld->DrawDebugData();

	_rWindow.setView( hudView );



	///draw HUD elements
		//todo: add code
	//end
	_rWindow.draw(HudRect);
	_rWindow.draw(HudViewHealth);
	_rWindow.draw(HudViewCoins);

	//_rWindow.draw( mousePosition );

	_rWindow.display();

}

void Level1::HandleInput(Event gameEvent)
{
	if ( gameEvent.type == Event::KeyPressed )
	{
		if(Keyboard::isKeyPressed(Keyboard::F10))
		{
			LState=Complete;
		}

		if ( gameEvent.key.code == Keyboard::C ) //spawn box
		{
			Vector2i mousePos = Mouse::getPosition( _rWindow );


		}

		if ( gameEvent.key.code == Keyboard::A ) //spawn box
		{
			cameraCenter -= 10;
		}

		if ( gameEvent.key.code == Keyboard::S ) //spawn box
		{
			cameraCenter += 10;
		}

		if ( gameEvent.key.code == Keyboard::B ) //spawn ball
		{
			Vector2i mousePos = Mouse::getPosition( _rWindow );


		}

		if ( gameEvent.key.code == Keyboard::C ) //increase ball radius
		{}

		if ( gameEvent.key.code == Keyboard::Q ) //decrease ball radius
		{}

		if ( gameEvent.key.code == Keyboard::E ) //explode
		{

		}

	}
}

void Level1::SpreadPickupCoins()
{
	vector<b2Vec2> locations;

	locations.push_back( b2Vec2(510, 700-48-48-48-48-50) );
	locations.push_back( b2Vec2(670, 700-48-48-48-48-48-48-50) );
	locations.push_back( b2Vec2(515, 700-48-48-48-48-48-48-48-48-50-15) );
	locations.push_back( b2Vec2(645, 700-48-48-48-48-48-48-48-48-48-48-50-40) );
	locations.push_back( b2Vec2(910, 700-48-48-48-48-48-48-48-48-50) );
	locations.push_back( b2Vec2(990, 700-48-48-48-48-48-48-48-48-50) );
	locations.push_back( b2Vec2(1105, 700-48-48-48-48-48-48-48-50-10) );
	locations.push_back( b2Vec2(1195, 700-48-48-48-48-48-48-48-50-10) );
	//locations.push_back( b2Vec2(810, 190) );
	//locations.push_back( b2Vec2(170, 280) );

	for ( int i = 0; i < locations.size(); ++i)
	{
		Coin* c = new Coin;
		c->Create(textureBank["coin"], locations[i].x, locations[i].y);
		c->IamA( COIN )->ICollideWith( EDWARD );
		c->SetWorld(*_pWorld);


		coins.push_back(c);

	}
}

void Level1::SpreadBrickPlatforms()
{
	vector<b2Vec2> locations;
	locations.push_back( b2Vec2(550 , 700-48-48-48-40) );
	locations.push_back( b2Vec2(630, 700-48-48-48-48-48-40) );
	locations.push_back( b2Vec2(560, 700-48-48-48-48-48-48-48-48-15) );
	locations.push_back( b2Vec2(700 , 700-48-48-48-48-48-48-48-48-48-48-40) );

	locations.push_back( b2Vec2(950, 700-48-48-48-48-48-48-48-48) );

	locations.push_back( b2Vec2(1145, 700-48-48-48-48-48-48-48-10) );
	//locations.push_back( b2Vec2(1075 + 450, 700-48-48-48-48-48-48-48-48) );

	for ( int i = 0; i < locations.size(); ++i)
	{
		StaticPlatform brickPlatform(textureBank["brickStone"], locations[i].x, locations[i].y, (int)4, 0.35f);

		brickPlatform.IamA( BRICK_PLATFORM )->ICollideWith( RANGER | EDWARD );
		brickPlatform.SetWorld(*_pWorld);

		platforms.push_back( brickPlatform );

	}
}

void Level1::SpreadTrees()
{
	vector<b2Vec2> locations;

	locations.push_back( b2Vec2(875 , 700-48-48-48) );
	locations.push_back( b2Vec2(1075 , 700-48-48-48) );
	locations.push_back( b2Vec2(850, 700-48-48-48) );
	locations.push_back( b2Vec2(650+150, 700-48-48-48) );
	locations.push_back( b2Vec2(600+150+120, 700-48-48-48) );
	locations.push_back( b2Vec2(1300, 700-48-48-48) );
	locations.push_back( b2Vec2(1300, 700-48-48-48) );
	locations.push_back( b2Vec2(1400, 700-48-48-48) );
	locations.push_back( b2Vec2(1600, 700-48-48-48) );
	locations.push_back( b2Vec2(2000, 700-48-48-48) );
	locations.push_back( b2Vec2(100, 700-48-48-48) );
	locations.push_back( b2Vec2(1350, 700-48-48-48) );
	//locations.push_back( b2Vec2(805, 70) );
	//locations.push_back( b2Vec2(805, 70) );


	for ( int i = 0; i < locations.size(); ++i)
	{
		StaticPlatform tree(textureBank["treeTexture"], locations[i].x, locations[i].y - 10, 1);
		tree.IamA( TREE )->ICollideWith( UNKNOWN );
		tree.SetWorld(*_pWorld);

		platforms.push_back( tree );
	}


}


void Level1::DrawMousePosition()
{

	//Vector2i p = Mouse::getPosition(_rWindow);

	//String pos = "( " + to_string((long double)p.x) +  " , " + to_string((long double)p.y) + " ) ";

	//mousePosition.setString( "test" );
	////position.setPosition( p.x, p.y );
	//_rWindow.draw( mousePosition );
}
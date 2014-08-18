#include "CollisionListener.h"



CollisionListener::CollisionListener()
{
}


CollisionListener::~CollisionListener()
{
}

void CollisionListener::BeginContact(b2Contact* contact)
{
	//GameObject* objectA = (GameObject *)contact->GetFixtureA()->GetBody()->GetUserData();
	//GameObject* objectB = (GameObject *)contact->GetFixtureB()->GetBody()->GetUserData();

	//if ( objectA == NULL || objectB == NULL ) { return; }

	uint16 objectA = contact->GetFixtureA()->GetFilterData().categoryBits;
	uint16 objectB = contact->GetFixtureB()->GetFilterData().categoryBits;

	//cout << "some collision detection" << endl;
	
	
	if (  objectA == EDWARD && objectB == BRICK_PLATFORM )
	{
		/*cout << "edward collides with brick platform";*/
		

	}

	if ( objectA == BRICK_PLATFORM && objectB == EDWARD ) 
	{
		//cout << "edward collides with brick platform";
		
	}

		
	if (  objectA == EDWARD && objectB == SPIKE_BALL )
	{
		
		Player* a = (Player *)contact->GetFixtureA()->GetBody()->GetUserData();
		a->Damage( 20 );
		/*cout << "edward collides with spike platform";*/
	}

	if ( objectA == SPIKE_BALL && objectB == EDWARD ) 
	{
		Player* a = (Player *)contact->GetFixtureB()->GetBody()->GetUserData();
		a->Damage( 20 );
		/*cout << "edward collides with spike platform";*/
	}

			
	if (  objectA == EDWARD && objectB == BLADE )
	{
		/*cout << "edward collides with blade";*/
		Player* a = (Player *)contact->GetFixtureA()->GetBody()->GetUserData();
		a->Damage( 20 );

		//contact->GetFixtureA()->GetBody()->GetWorld()->DestroyBody( contact->GetFixtureA()->GetBody() );
	}

	if ( objectA == BLADE && objectB == EDWARD ) 
	{
		/*cout << "edward collides with blade";*/
		Player* a = (Player *)contact->GetFixtureB()->GetBody()->GetUserData();
		a->Damage( 20 );

		//contact->GetFixtureA()->GetBody()->GetWorld()->DestroyBody( contact->GetFixtureA()->GetBody() );
	
	}
	if ( objectA == SPIKE && objectB == EDWARD )
	{
	/*	cout << "edward collides with Spike";*/

		Player* a = (Player *)contact->GetFixtureB()->GetBody()->GetUserData();
		a->Damage( 10 );

	}
	
	if ( objectB == SPIKE && objectA == EDWARD )
	{/*
		cout << "edward collides with Spike";*/

		Player* a = (Player *)contact->GetFixtureA()->GetBody()->GetUserData();
		a->Damage( 10 );

	}


	if ( objectA ==	COIN && objectB == EDWARD )
	{
		/*cout << "coin collected\n";*/

		Coin *a = (Coin *)contact->GetFixtureA()->GetBody()->GetUserData();
		a->isCollected=true;
		
		

	}
	
	if ( objectB == COIN && objectA == EDWARD )
	{
		
		/*cout << "coin collected\n";*/
		Coin *a = (Coin *)contact->GetFixtureB()->GetBody()->GetUserData();
		a->isCollected=true;
		

	}


	if ( objectA ==	BLADE && objectB == EDWARD )
	{
		/*cout << "coin collected\n";*/

		Player *a = (Player *)contact->GetFixtureB()->GetBody()->GetUserData();
		a->Damage(20);
		
	}
	
	if ( objectB == BLADE && objectA == EDWARD )
	{
		/*
		cout << "coin collected\n";*/
		Player *a = (Player *)contact->GetFixtureA()->GetBody()->GetUserData();
		a->Damage(20);
		

	}


	if (objectA == EDWARD && objectB == KNIFE)
	{/*
		cout << "edward collides with knife";*/
		Player* a = (Player *)contact->GetFixtureA()->GetBody()->GetUserData();
		a->Damage(20);

		Projectile* p = (Projectile *)contact->GetFixtureB()->GetBody()->GetUserData();
		p->ContactMade();
		//contact->GetFixtureA()->GetBody()->GetWorld()->DestroyBody( contact->GetFixtureA()->GetBody() );
	}

	if (objectA == KNIFE && objectB == EDWARD)
	{
	/*	cout << "edward collides with kknife";*/
		Player* a = (Player *)contact->GetFixtureB()->GetBody()->GetUserData();
		a->Damage(20);

		Projectile* p = (Projectile *)contact->GetFixtureA()->GetBody()->GetUserData();
		p->ContactMade();
		//contact->GetFixtureA()->GetBody()->GetWorld()->DestroyBody( contact->GetFixtureA()->GetBody() );

	}

	
}


void CollisionListener::EndContact(b2Contact* contact)
{

}
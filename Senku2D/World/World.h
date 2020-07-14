#pragma once
#include "Rigid Body List.h"
#include "../Rigid Body/Collision Processing/Collision Detection/Broad Phase.h"
#include "../Rigid Body/Collision Processing/Collision Detection/Narrow Phase.h"
#include "../Rigid Body/Collision Processing/Collision Resolution/Collision Resolver.h"

namespace Senku2D
{
	//Default World Screen Position and Size
	const Vector2 SCREEN_POSITION = Vector2(0, 0);
	const Vector2 SCREEN_SIZE = Vector2(1200, 700);

	//Fixed Limit of Potential Contacts That Can be Generated
	const uint8_t POTENTIAL_CONTACT_LIST_LIMIT = 4;
	//Local Potential Contact Limit
	const uint8_t LOCAL_POTENTIAL_CONTACT_LIMIT = 3;

	//Maximum Amount of Contacts Generated
	const unsigned int MAX_CONTACTS = 24;

	//A Physics World Class
	/*
	This Class is the Coordinator of Everything in the Physics World.
	This is Currently NOT a Singleton Class But Should Only have One Instance of It
	Since You Only Need One Physics World for Everything!
	*/
	class World
	{
	private:
		//Reference to the Rigid Body List
		RigidBodyList& m_RigidBodyList;

		//Quadtree
		Quadtree m_Quadtree;

		//Update All Bodies
		void IntegrateAllBodies(const Real& Timestep);
	public:
		//Constructor
		World();
		//Destructor
		~World();

		//Adding a Rigid Body to the Global List
		void AddBody(RigidBody* rRB);
		//Removing a Rigid Body to the Global List
		void DestroyBody(RigidBody* rRB);

		//Update the World
		void Update(const Real& Timestep);
	};
}

#pragma once
#include "Rigid Body List.h"
#include "../Rigid Body/Collision Processing/Collision Detection/Broad Phase.h"
#include "../Rigid Body/Collision Processing/Collision Detection/Narrow Phase.h"
#include "../Rigid Body/Collision Processing/Collision Resolution/Collision Resolver.h"
#include "Rigid Body Contact Pair List.h"
#include <chrono>

namespace Senku2D
{
	//Fixed Limit of Potential Contacts That Can be Generated
	const uint8_t POTENTIAL_CONTACT_LIST_LIMIT = 10;
	//Local Potential Contact Limit
	const uint8_t LOCAL_POTENTIAL_CONTACT_LIMIT = 8;

	//World Arena Scale Factor
	const Real WORLD_ARENA_SCALE_FACTOR = 2.0f;

	//Default World Arena Position and Size
	const Vector2 DEFAULT_WORLD_ARENA_POSITION = Vector2(-1600.0f, -1200.0f);
	const Vector2 DEFAULT_WORLD_ARENA_SIZE = Vector2(3200.0f, 2400.0f) * 2.0f;

	//A Physics World Class
	/*
	This Class is the Coordinator of Everything in the Physics World.
	This is Currently NOT a Singleton Class But Should Only have One Instance of It
	Since You Only Need One Physics World for Everything!
	*/
	class World
	{
	private:
		//The Rigid Body List
		RigidBodyList m_RigidBodyList;

		//World Arena
		AABB WorldArena;

		//Final Potential Contact List
		PotentialContactList FinalPCList;
		//Primitive List Contact List
		PotentialContactList PrimitiveTestResultList;

		//Contact List
		ContactList ContactPairList;

		//Collision Resolver
		CollisionResolver _CollisionResolver;

		//Update All Bodies
		void IntegrateAllBodies(const Real& Timestep);
	public:
		//Default Constructor
		World();
		//Destructor
		~World();

		//Adding a Rigid Body to the Global List
		void AddBody(RigidBody* rRB);
		//Removing a Rigid Body to the Global List
		void DestroyBody(RigidBody* rRB);

		//Setting World Position and Size
		void SetWorldArena(const Vector2& Position, const Vector2& Size);

		//Update the World
		void Update(const Real& Timestep, RigidBodyPairList& CollidingPairsList);
	};
}

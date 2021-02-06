#pragma once
#include "Rigid Body List.h"
#include "../Rigid Body/Collision Processing/Collision Detection/Broad Phase.h"
#include "../Rigid Body/Collision Processing/Collision Detection/Narrow Phase.h"
#include "../Rigid Body/Collision Processing/Collision Resolution/Collision Resolver.h"
#include "Rigid Body Contact Pair List.h"
#include "../Rigid Body/Collision Processing/Hashed Grid/Grid.h"

namespace Senku2D
{
	//Fixed Limit of Potential Contacts That Can be Generated
	const size_t DEFAULT_POTENTIAL_CONTACT_LIST_LIMIT = 128;
	
	//World Arena Scale Factor
	const Real WORLD_ARENA_SCALE_FACTOR = 2.0f;

	//Default World Arena Position and Size
	const Vector2 DEFAULT_WORLD_ARENA_POSITION = Vector2(-1600.0f, -1200.0f);
	const Vector2 DEFAULT_WORLD_ARENA_SIZE = Vector2(3200.0f, 2400.0f) * 2.0f;

	//A Physics World Class
	/*
	** This Class is the Coordinator of Everything in the Physics World.
	** Only One Instance of this Class Needs to Exist
	** Since You Only Need One Physics World for Everything!
	*/
	class World
	{
	private:
		//The Rigid Body List
		RigidBodyList m_RigidBodyList;

		//Final Potential Contact List
		PotentialContactList FinalPCList;
		//Primitive List Contact List
		PotentialContactList PrimitiveTestResultList;

		//Contact List
		ContactList ContactPairList;

		//Collision Resolver
		CollisionResolver _CollisionResolver;

		//Broad Phase
		//Dynamic Grid (Holds Only Dynamic Bodies)
		HashedGrid::Grid DynamicGrid;
		//Static Grid (Holds Only Static Bodies)
		HashedGrid::Grid StaticGrid;
		
		//Need to Rebuild Static Grid?
		const bool& rRebuildStaticGrid;
		
		//Update All Bodies
		void IntegrateAllBodies(const Real& Timestep);
	public:
		//Default Constructor
		World();

		//Parameterized Constructor
		/*
		** PotentialContactsLimit - Maximum Number of Potential Contacts to 
		**							Check during Collision Detection.
		** ContactsLimit - Maximum Number of Contacts to Check and
		**				   Resolve during Collision Detection.
		*/
		World(const size_t& PotentialContactsLimit,
			const size_t& ContactsLimit);

		//Destructor
		~World();

		//Setting World Division Size
		/*
		** Senku2D Uses a Hashed Grid for Broad Phase Collision Detection thus it Needs a
		** Cell Division Size. The Default Value is 128 x 128 Pixels. 
		** This Size Should not be too Fine or too Coarse!
		*/
		void SetCellDivisionSize(const Real& CellWidth, const Real& CellHeight);

		//Adding a Rigid Body to the World
		void AddBody(RigidBody* rRB);
		//Removing a Rigid Body from the World
		void DestroyBody(RigidBody* rRB);

		//Updating the World
		/*
		** CollidingPairsList - This List will Contain the Pair of Rigid Bodies 
		**						Currently in Contact. This can be used for Doing
		**						Special Effects when Two Specific Bodies Collide!
		*/
		void Update(const Real& Timestep, RigidBodyPairList& CollidingPairsList);

		//Raycasting
		/*
		** World can be Queried for Rigid Bodies By Casting a Ray From One Point to Another
		** Point. This Function Returns the Number of Bodies Found by the Ray Cast Query and
		** Fills Up the Given Array of Rigid Body Pointers till it Reaches the Given Size.
		** An Array of Pointers Can be Defined Like This - RigidBody* Bodies[Size];
		*/
		unsigned int RayCast(Ray& QueryRay, RigidBody** BodiesFound, const size_t& Size);
	};
}

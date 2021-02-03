#pragma once
#include "../../../World/Rigid Body List.h"
#include "../Hashed Grid/Grid.h"

namespace Senku2D
{
	//A Class for Broad Phase Collision Detection
	class BroadPhase
	{
	public:
		//Inserting Dynamic Bodies to a Hashed Grid
		static void InsertDynamicBodiesToGrid(HashedGrid::Grid* pGrid, RigidBodyList* pRBList);
		
		//Inserting Static Bodies to a Hashed Grid
		static void InsertStaticBodiesToGrid(HashedGrid::Grid* pGrid, RigidBodyList* pRBList);


		//Querying Dynamic Bodies Using a Hashed Grid
		/*
		** Uses the Grid's Active Cell Query Function to Check Dynamic vs Dynamic Collision.
		*/
		static unsigned int QueryDynamicBodiesUsingGrid(HashedGrid::Grid* pGrid, 
			PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts = 0);
	
		//Querying Dynamic Bodies Against Static Bodies
		/*
		** Uses the Grid's RigidBody Query Function to Check Static vs Dynamic Collision.
		*/
		static unsigned int QueryStaticBodiesUsingGrid(HashedGrid::Grid* pGrid, 
			RigidBodyList* pRBList, PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts = 0);
	};
}

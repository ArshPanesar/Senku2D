#pragma once
#include "../Quadtree.h"
#include "../../../World/Rigid Body List.h"

namespace Senku2D
{
	//A Service Class for Broad Phase Collision Detection
	class BroadPhase
	{
	public:
		//Inserting Bodies to a Quadtree
		static void InsertBodiesToQuadtree(Quadtree* pQuadtree, RigidBodyList& List);

		//Query Neighbours of a Specific Body from a Quadtree
		//Returns the Number of Potential Contacts Generated
		static unsigned int QueryNeighboursFromQuadtree(Quadtree* pQuadtree, RigidBody* pRB, PotentialContactList* pContacts);
	};
}

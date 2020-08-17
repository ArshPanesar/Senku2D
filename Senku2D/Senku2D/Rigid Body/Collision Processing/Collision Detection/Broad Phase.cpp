#include "Broad Phase.h"

void Senku2D::BroadPhase::InsertBodiesToQuadtree(Quadtree* pQuadtree, RigidBodyList& List)
{
	for (unsigned int i = 0; i < List.GetDynamicBodyListSize(); ++i)
	{
		pQuadtree->Insert(List.GetRigidBodyFromDynamicList(i));
	}
}

unsigned int Senku2D::BroadPhase::QueryNeighboursFromQuadtree(Quadtree* pQuadtree, RigidBody* pRB, PotentialContactList* pContacts)
{
	return pQuadtree->Query(pRB, pContacts);
}


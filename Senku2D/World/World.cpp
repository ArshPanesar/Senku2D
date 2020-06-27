#include "World.h"

void Senku2D::World::IntegrateAllBodies(const Real& Timestep)
{
	//Go Through the List
	for (size_t i = 0; i < m_RigidBodyList.GetSize(); ++i)
	{
		//Integrate Body
		m_RigidBodyList.GetRigidBody(i)->Integrate(Timestep);
	}
}

Senku2D::World::World()	:
	m_RigidBodyList(RigidBodyList::Get()),
	m_Quadtree(SCREEN_POSITION, SCREEN_SIZE, 0)
{

}

Senku2D::World::~World()
{
	//Clearing the List
	m_RigidBodyList.Clear();
}

void Senku2D::World::AddBody(RigidBody* rRB)
{
	m_RigidBodyList.Add(rRB);
}

void Senku2D::World::DestroyBody(RigidBody* rRB)
{
	if (!rRB->IsDestroyed())
	{
		rRB->Destroy();
		m_RigidBodyList.Remove(rRB);
	}
}

void Senku2D::World::Update(const Real& Timestep)
{
	//Update All Bodies
	IntegrateAllBodies(Timestep);

	//Collision Detection
	//
	//Potential Contact List
	PotentialContactList PCList;
	//
	//Broad Phase
	//Inserting All Bodies Into the Quadtree
	BroadPhase::InsertBodiesToQuadtree(&m_Quadtree, m_RigidBodyList);
	//
	//Traversing the Body List
	for (unsigned int i = 0; i < m_RigidBodyList.GetSize(); ++i)
	{
		//Querying a Rigid Body from the QuadTree
		unsigned int NumOfPotentialContacts = BroadPhase::QueryNeighboursFromQuadtree(&m_Quadtree, m_RigidBodyList.GetRigidBody(i), &PCList);
		//
		//Potential Contacts Generated!

		//Continue if No Contacts Were Found
		if (NumOfPotentialContacts == 0)
		{
			continue;
		}

		//Narrow Phase Collision Detection


		//Clearing the List
		PCList.Clear();
	}

	//Clearing the Quadtree
	m_Quadtree.Clear();
}

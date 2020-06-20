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
	m_RigidBodyList(RigidBodyList::Get())
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
	rRB->Destroy();
	m_RigidBodyList.Remove(rRB);
}

void Senku2D::World::Update(const Real& Timestep)
{
	//Update All Bodies
	IntegrateAllBodies(Timestep);
}

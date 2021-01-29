#include "World.h"

void Senku2D::World::IntegrateAllBodies(const Real& Timestep)
{
	//Go Through the List
	for (size_t i = 0; i < m_RigidBodyList.GetDynamicBodyListSize(); ++i)
	{
		//Integrate Body
		m_RigidBodyList.GetRigidBodyFromDynamicList(i)->Integrate(Timestep);
	}
}

Senku2D::World::World()	:
	m_RigidBodyList(),
	WorldArena(DEFAULT_WORLD_ARENA_POSITION, DEFAULT_WORLD_ARENA_SIZE),
	FinalPCList(POTENTIAL_CONTACT_LIST_LIMIT),
	PrimitiveTestResultList(POTENTIAL_CONTACT_LIST_LIMIT),
	ContactPairList(MAX_CONTACTS)
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

void Senku2D::World::SetWorldArena(const Vector2 & Position, const Vector2 & Size)
{
	//Setting Scaled Position and Size for the World
	WorldArena.Position = Position;
	WorldArena.Size = Size;
	WorldArena.Position -= Vector2(WorldArena.Size * WORLD_ARENA_SCALE_FACTOR);
	WorldArena.Size *= WORLD_ARENA_SCALE_FACTOR * 2.0f;
}

void Senku2D::World::Update(const Real& Timestep, RigidBodyPairList& CollidingPairsList)
{
	//Timer
	/*
	auto t1 = std::chrono::high_resolution_clock::now();
	auto t2 = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	PRT(duration);
	*/

	//Update All Bodies
	IntegrateAllBodies(Timestep);
	
	//Clearing the List
	CollidingPairsList.Clear();

	//Collision Detection
	//
	//Final Potential Contact List
	FinalPCList.Clear();
	
	//Broad Phase
	//
	//Total Number of Contacts Found
	unsigned int TotalNumOfPotentialContactsFound = 0;
	//
	//If There are No Potential Contacts Then Dont Do Anything
	if (TotalNumOfPotentialContactsFound == 0)
	{
		return;
	}
	//


	//Final Potential Contacts Generated!
	//
	//Narrow Phase Collision Detection
	PrimitiveTestResultList.Clear();
	//Generating Resultant List From Final List
	unsigned int PrimitiveTestResult = NarrowPhase::GeneratePrimitiveTestResultsList(&FinalPCList, &PrimitiveTestResultList);
	//Collision Detected List: Shape Test List
	ContactPairList.Clear();
	//Generating Shape Result List
	unsigned int NumOfContactsFound = NarrowPhase::GenerateShapeTestResultsList(&PrimitiveTestResultList, &ContactPairList);


	//Collision Detection Completed!
	//
	if (NumOfContactsFound > 0)
	{
		//Now We Have A List of Actual Colliding Pair of Rigid Bodies
		//
		//
		//Resolving the Collision Pairs
		_CollisionResolver.Resolve(&ContactPairList, Timestep);
		//
		//Copying the Collision Pair List
		CollidingPairsList.CopyFromContactList(ContactPairList);
	}
	//End Of Physics Update
}

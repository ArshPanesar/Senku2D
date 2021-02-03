#include "World.h"

void Senku2D::World::IntegrateAllBodies(const Real& Timestep)
{
	//Go Through the List
	const size_t& Size = m_RigidBodyList.GetDynamicBodyListSize();
	for (size_t i = 0; i < Size; ++i)
	{
		//Integrate Body
		m_RigidBodyList.GetRigidBodyFromDynamicList(i)->Integrate(Timestep);
	}
}

Senku2D::World::World()	:
	m_RigidBodyList(),
	FinalPCList(DEFAULT_POTENTIAL_CONTACT_LIST_LIMIT),
	PrimitiveTestResultList(DEFAULT_POTENTIAL_CONTACT_LIST_LIMIT),
	ContactPairList(DEFAULT_MAX_CONTACTS),
	DynamicGrid(),
	StaticGrid(),
	rRebuildStaticGrid(EventInterface::Get().ShouldRedoStaticGrid())
{

}

Senku2D::World::World(const size_t& PotentialContactsLimit, const size_t& ContactsLimit)	:
	m_RigidBodyList(),
	FinalPCList(PotentialContactsLimit),
	PrimitiveTestResultList(ContactsLimit),
	ContactPairList(ContactsLimit),
	DynamicGrid(),
	StaticGrid(),
	rRebuildStaticGrid(EventInterface::Get().ShouldRedoStaticGrid())
{

}

Senku2D::World::~World()
{
	//Clearing the List
	m_RigidBodyList.Clear();
}

void Senku2D::World::SetCellDivisionSize(const Real& CellWidth, const Real& CellHeight)
{
	StaticGrid.SetCellSize(CellWidth, CellHeight);
	DynamicGrid.SetCellSize(CellWidth, CellHeight);

	//Rebuild Static Grid with New Cell Size
	//Clearing the Grid
	StaticGrid.Clear();
	//Inserting Static Body to Respective Hashed Grid
	BroadPhase::InsertStaticBodiesToGrid(&StaticGrid, &m_RigidBodyList);
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
	//Clearing the Grid for Current Frame
	DynamicGrid.Clear();
	
	//Inserting Dynamic Bodies to Hashed Grid For this and the Next Frame
	BroadPhase::InsertDynamicBodiesToGrid(&DynamicGrid, &m_RigidBodyList);
	
	//Rebuilding Static Grid if Needed
	if (rRebuildStaticGrid)
	{
		//Clearing the Grid
		StaticGrid.Clear();

		//Inserting Static Body to Respective Hashed Grid
		BroadPhase::InsertStaticBodiesToGrid(&StaticGrid, &m_RigidBodyList);

		EventInterface::Get().SetRedoStaticGrid(false);
	}
	
	//Querying Each Active Cell
	unsigned int TotalNumOfPotentialContactsFound = BroadPhase::QueryDynamicBodiesUsingGrid(&DynamicGrid, &FinalPCList);	
	//Querying Static vs Dynamic
	TotalNumOfPotentialContactsFound += BroadPhase::QueryStaticBodiesUsingGrid(&StaticGrid, &m_RigidBodyList, &FinalPCList, TotalNumOfPotentialContactsFound);
	
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
	unsigned int PrimitiveTestResult = NarrowPhase::GeneratePrimitiveTestResultsList(
		&FinalPCList, &PrimitiveTestResultList, TotalNumOfPotentialContactsFound);
	
	//Collision Detected List: Shape Test List
	ContactPairList.Clear();
	//Generating Shape Result List
	unsigned int NumOfContactsFound = NarrowPhase::GenerateShapeTestResultsList(
		&PrimitiveTestResultList, &ContactPairList, PrimitiveTestResult);
	
	//Collision Detection Completed!
	//
	if (NumOfContactsFound > 0)
	{
		//Now We Have A List of Actual Colliding Pair of Rigid Bodies
		//Resolving the Collision Pairs
		_CollisionResolver.Resolve(&ContactPairList, Timestep);
		
		//Copying the Collision Pair List
		CollidingPairsList.CopyFromContactList(ContactPairList);
	}
	//End Of Physics Update
}
